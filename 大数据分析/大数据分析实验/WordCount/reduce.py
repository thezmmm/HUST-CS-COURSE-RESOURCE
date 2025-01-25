import sys
import threading
import time

def reduce(readfile, writefile):
    file_path = './data/'
    file = open(file_path+readfile, 'r')
    write = open(file_path+writefile, 'w')
    count_dict = {}
    for line in file:
        line = line.strip()
        word, count = line.split(',', 1)
        try:
            count = int(count)
        except ValueError:
            continue
        if word in count_dict.keys():
            count_dict[word] = count_dict[word] + count
        else:
            count_dict[word] = count

    count_dict = sorted(count_dict.items(), key=lambda x: x[0], reverse=False)
    for key, v in count_dict:
        write.write("{},{}\n".format(key, v))

if __name__ == '__main__':
    start_time = time.perf_counter()
    start = time.perf_counter()
    t1 = threading.Thread(target=reduce('shuffle1', 'reduce1'), args=("t1",))
    t2 = threading.Thread(target=reduce('shuffle2', 'reduce2'), args=("t2",))
    t3 = threading.Thread(target=reduce('shuffle3', 'reduce3'), args=("t3",))
    t1.start()
    t2.start()
    t3.start()

    t1.join()
    print("t1 cost %s s" % (time.perf_counter() - start))
    t2.join()
    print("t2 cost %s s" % (time.perf_counter() - start))
    t3.join()
    print("t3 cost %s s" % (time.perf_counter() - start))

    end_time = time.perf_counter()
    total_time = float(end_time - start_time)
    print("total time: %f s" % total_time)
    print("Estimated total time without map-reduce: %f s" % (total_time * 3))