# -*- coding: utf-8 -*-

def create_grid(left, right, N):
    """
    Создание генератора разбиения квадрата
    """
    def generate_grid_on_line(left, right):
        tmp = (right - left) / (2 * N)
        l = left + tmp
        for _ in xrange(1, 2 * N, 2):
            yield l
            l += 2 * tmp
    
    def fix_point(current_fixed):
        current_unfixed = len(current_fixed)
        if current_unfixed == len(left):
            yield current_fixed
        else:
            point_generator = generate_grid_on_line(left[current_unfixed],
                                                    right[current_unfixed])
            for coord in point_generator:
                for i in fix_point(current_fixed + [coord]):
                    yield i
        
    return fix_point([])    


if __name__ == '__main__':
    pass
