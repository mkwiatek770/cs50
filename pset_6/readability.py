import re


def get_grade(L, S):
    return round(0.0588 * L - 0.296 * S - 15.8)


def word_length(word):
    return len(re.sub("[!?'\.]", '', word))
    

def get_average_n_of_letters_per_100_words(text):
    words = text.split()
    return round((sum(word_length(word) for word in words) / len(words)) * 100, 2)


def get_average_n_of_words_per_sentence(text):
    sentences = re.split('[!?\.]', text)
    words = text.split()
    return round(((len(sentences) - 1) / len(words)) * 100, 2)


if __name__ == '__main__':
    text = input('Text: ')
    l = get_average_n_of_letters_per_100_words(text)
    s = get_average_n_of_words_per_sentence(text)
    print("Grade ", get_grade(l, s))
