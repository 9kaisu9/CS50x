from cs50 import get_int, get_string


def digit_from_front(number, n):
    number_list = [int(x) for x in str(number)]
    return number_list[n]


def digits(number):
    count = 0
    while number != 0:
        number //= 10
        count += 1
    return count
    

def valid_sum(number):
    number_list = [int(x) for x in str(number)]
    number_list_backwards = number_list[::-1]
    check = 0
    for index, value in enumerate(number_list_backwards):
        if index % 2 == 1:
            if digits(value * 2) > 1:
                sub_number_list = [int(x) for x in str(value * 2)]
                for sub_value in sub_number_list:
                    check += sub_value
            else:
                check += value * 2
        else:
            check += value
    if check % 10 == 0:
        return True
    else:
        return False


number = get_int("Number: ")

if valid_sum(number):
    if digits(number) == 13:
        if digit_from_front(number, 0) == 4:
            print("VISA")
        else:
            print("INVALID")
    elif digits(number) == 15:
        if digit_from_front(number, 0) == 3 and (digit_from_front(number, 1) == 4 or digit_from_front(number, 1) == 7):
            print("AMEX")
        else:
            print("INVALID")
    elif digits(number) == 16:
        if digit_from_front(number, 0) == 4:
            print("VISA")
        elif digit_from_front(number, 0) == 5 and digit_from_front(number, 1) > 0 and digit_from_front(number, 1) < 6:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")