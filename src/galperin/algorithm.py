def minimize(f):
    def get_point(X, Y, Z):
        """
        Функция определения следующей точки, принадлежащей W_i
        X, Y, Z кортежи (радиус, [центр]) соответствующих множеств
        """
        pass
    
    def split_points(points):
        """
        Разделение точек на множества X, Y, Z
        """
        pass
    
    def stop_rule(points):
        """
        ???
        """
        pass
    
    points = []
    p = 100500
    X, Y, Z = [], [], []
    while (not stop_rule(points)):
        x = get_point(X, Y, Z)
        p = min(p, f(x))
        points.append(x)
        X, Y, Z = split_points(points)
    return X + Y