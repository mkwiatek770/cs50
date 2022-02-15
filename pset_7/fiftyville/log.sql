-- Keep a log of any SQL queries you execute as you solve the mystery.


-- schema
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE courthouse_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);

-- get information about crimes on 2020.07.28 Chamberlin Street
SELECT description FROM crime_scene_reports
WHERE (year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street');
-- result: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
--         Interviews were conducted today with three witnesses who were present at the
--         time — each of their interview transcripts mentions the courthouse.


-- get transcripts of 3 interviews who says something about courthouse
SELECT name, transcript FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE '%courthouse%';
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Ruth: get license plates
SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 30 AND activity = 'exit';
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Eugene: withdrawing money the same day before the theft date
SELECT account_number, amount FROM atm_transactions
WHERE atm_location = 'Fifer Street' AND year = 2020 AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
-- 28500762|48
-- 28296815|20
-- 76054385|60
-- 49610011|50
-- 16153065|80
-- 25506511|20
-- 81061156|30
-- 26013199|35


-- get earliest flight FROM Fiftyville on 29th July 2020
WITH suspect_passports AS (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
            SELECT id FROM flights
            WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
            AND year = 2020 AND month = 7 AND day = 29
            ORDER BY hour, minute
            LIMIT 1
    )
)

-- 36|8|4|2020|7|29|8|20



-- 1. combine those two to find a guilty person
WITH suspected_plates AS (
    SELECT license_plate FROM courthouse_security_logs
    WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit'
),
suspected_account_ids AS (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (SELECT account_number FROM atm_transactions
                             WHERE atm_location = 'Fifer Street' AND year = 2020
                             AND month = 7 AND day = 28 AND transaction_type = 'withdraw')
),
suspected_passports AS (
    SELECT passport_number FROM passengers
    WHERE flight_id = (
            SELECT id FROM flights
            WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
            AND year = 2020 AND month = 7 AND day = 29
            ORDER BY hour, minute
            LIMIT 1
    )
),
suspect_numbers AS (
    SELECT caller FROM phone_calls
    WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
)
SELECT name FROM people
WHERE 
    license_plate IN suspected_plates
    AND id IN suspected_account_ids
    AND passport_number IN suspected_passports
    AND phone_number IN suspect_numbers;
-- Ernest

