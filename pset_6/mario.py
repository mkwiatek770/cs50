
def get_height() -> int:
    valid_height = False
    while not valid_height:
        try:
            height = int(input("Height: "))
        except ValueError:
            ...
        else:
            if height > 0 and height <= 8:
                valid_height = True
    return height


def build(n):
    for i in range(1, n + 1):
        print('{0:>{x}}  {0}'.format('#' * i, x=n))


if __name__ == '__main__':
    height = get_height()
    build(height)

