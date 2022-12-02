from cs50 import get_string


def count_letters(text):
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    letters = 0
    for char in text:
        if char.lower() in alphabet:
            letters += 1
    return letters


def count_words(text):
    words = 1
    for char in text:
        if char == " ":
            words += 1
    return words


def count_sentences(text):
    sentence_marker = ".!?"
    sentences = 0
    for char in text:
        if char in sentence_marker:
            sentences += 1
    return sentences
    

text = get_string("Text: ")
letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

index = 0.0588 * (letters * 100 / words) - 0.296 * (sentences * 100 / words) - 15.8

if index < 1:
    print("Before Grade 1\n")
elif index >= 16:
    print("Grade 16+\n")
else:
    print(f"Grade {round(index)}")