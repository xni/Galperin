def calculate_center(left, right):
    return map(lambda x, y: 0.5 * (x + y), left, right)


def cube_side(left, right):
    return right[0]-left[0]

