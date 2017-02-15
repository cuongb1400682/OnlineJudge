from random import choice


# Monte carlo algorithm to determine whether a sequence is sorted or not
def is_sorted(my_list):
    ans = 0
    is_first_choice = True
    for i in range(0, 100):
        first_num = choice(range(0, len(my_list)))
        second_num = choice(range(0, len(my_list)))
        if first_num > second_num:
            first_num, second_num = second_num, first_num
        first_num = my_list[first_num]
        second_num = my_list[second_num]
        if is_first_choice:
            ans = second_num - first_num
            is_first_choice = False
        elif ans * (second_num - first_num) < 0:
            return 0
    return -1 if ans < 0 else 1


def main_func():
#    my_list = []
#    candidate = [i for i in range(0, 100000)]
#    while len(my_list) < 500:
#        entry = choice(candidate)
#        my_list.append(entry)
#        candidate.remove(entry)
#    print my_list
    my_list = [i for i in range(0, 100000)]
    
    my_list[0], my_list[10000] = my_list[10000], my_list[0]
    
    out_map = {-1: 'DEC', 0: 'RAN', 1: 'INC'}
    freq = {}
    for i in range(0, 100):
        tmp = out_map[is_sorted(my_list)]
        freq.setdefault(tmp, 0)
        freq[tmp] += 1
    for key in freq:
        print "%s: %s" % (key, freq[key])
    return 0


if __name__ == '__main__':
    exit(main_func())
