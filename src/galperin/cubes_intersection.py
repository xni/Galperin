import math

from galperin import calculate_center, cube_side


def cubes_in(left_j, right_j, left_k, right_k):
    c_j, c_k = cube_side(left_j, right_j), cube_side(left_k, right_k)
    t = 0.5 * (c_k - c_j)
    x_j= calculate_center(left_j, right_j)
    x_k = calculate_center(left_k, right_k)
    return all(map(lambda x, y: math.fabs(x - y) <= t, x_j, x_k))


def cubes_out(left_j, right_j, left_k, right_k):
    c_j, c_k = cube_side(left_j, right_j), cube_side(left_k, right_k)
    t = 0.5 * (c_k - c_j)
    x_j= calculate_center(left_j, right_j)
    x_k = calculate_center(left_k, right_k)
    return any(map(lambda x, y: math.fabs(x - y) > t, x_j, x_k))


def cubes_intersect(left_j, right_j, left_k, right_k):
    return ((not cubes_out(left_j, right_j, left_k, right_k)) and 
        (not cubes_in(left_j, right_j, left_k, right_k))) 


if __name__ == '__main__':
    pass
