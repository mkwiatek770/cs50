import re

# NUMBER_REGEX = re.compile(r'\d{13,16}')
NUMBER_REGEX = re.compile(r'\d*')
MASTERCARD_REGEX = re.compile(r'5[1-5]\d{14}')
VISA_REGEX = re.compile(r'4\d{12,15}')
AMEX_REGEX = re.compile(r'3[47]\d{13}')



def get_number() -> str:
    valid = False
    while not valid:
        number = input("Number: ")
        valid = NUMBER_REGEX.fullmatch(number)
    return number


def checksum(number: str):
    sum_products = 0
    sum_remaining = 0
    for num in number[-2::-2]:
        by_2 = int(num) * 2
        sum_products += by_2 // 10 + by_2 % 10
    for num in number[-1::-2]:
        sum_remaining += int(num)
    return (sum_remaining + sum_products) % 10 == 0


def valid_mastercard(number: str) -> bool:
    return MASTERCARD_REGEX.fullmatch(number)


def valid_american_express(number: str) -> bool:
    return AMEX_REGEX.fullmatch(number)


def valid_visa(number: str) -> bool:
    return VISA_REGEX.fullmatch(number) and checksum(number)


if __name__ == '__main__':
    number = get_number()
    if valid_mastercard(number):
        print("MASTERCARD")
    elif valid_american_express(number):
        print("AMEX")
    elif valid_visa(number):
        print("VISA")
    else:
        print("INVALID")
