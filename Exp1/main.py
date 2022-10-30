

if __name__ == "__main__":

    str1 = input("请输入一段文本:")
    ch = 0  # 汉字个数
    space = 0  # 空格个数
    alpha = 0  # 字母个数
    num = 0  # 数字个数
    dot = 0
    for i in str1:
        if u"\u4e00" <= i <= u"\u9fa5":  # 判断是否为汉字
            ch += 1
        elif i.isspace():  # 判断是否为空格
            space += 1
        elif i.isalpha():  # 判断是否为字母
            alpha += 1
        elif i.isdigit(): # 判断是否为数字
            num += 1
        else:  # 标点符号个数
            dot += 1

    print("汉字有%d个" % ch)
    print("空格有%d个" % space)
    print("字母有%d个" % alpha)
    print("数字有%d个" % num)
    print("标点符号有%d个" % dot)





