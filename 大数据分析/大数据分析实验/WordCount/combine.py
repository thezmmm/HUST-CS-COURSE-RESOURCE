import sys
import threading
import time

def combine(inputfile, outputfile):
    file_path = './data/'
    read = open(file_path+inputfile, 'r')
    write = open(file_path+outputfile, 'w')
    count_dict = {}
    for line in read:
        line = line.strip()
        word, count = line.split(',', 1)
        count = int(count)
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
    t1 = threading.Thread(target=combine('map1', 'combine1'), args=("t1",))
    t2 = threading.Thread(target=combine('map2', 'combine2'), args=("t2",))
    t3 = threading.Thread(target=combine('map3', 'combine3'), args=("t3",))
    t4 = threading.Thread(target=combine('map4', 'combine4'), args=("t4",))
    t5 = threading.Thread(target=combine('map5', 'combine5'), args=("t5",))
    t6 = threading.Thread(target=combine('map6', 'combine6'), args=("t6",))
    t7 = threading.Thread(target=combine('map7', 'combine7'), args=("t7",))
    t8 = threading.Thread(target=combine('map8', 'combine8'), args=("t8",))
    t9 = threading.Thread(target=combine('map9', 'combine9'), args=("t9",))
    t1.start()
    t2.start()
    t3.start()
    t4.start()
    t5.start()
    t6.start()
    t7.start()
    t8.start()
    t9.start()

    t1.join()
    print("t1: %s s" % (time.perf_counter() - start))
    t2.join()
    print("t2: %s s" % (time.perf_counter() - start))
    t3.join()
    print("t3: %s s" % (time.perf_counter() - start))
    t4.join()
    print("t4: %s s" % (time.perf_counter() - start))
    t5.join()
    print("t5: %s s" % (time.perf_counter() - start))
    t6.join()
    print("t6: %s s" % (time.perf_counter() - start))
    t7.join()
    print("t7: %s s" % (time.perf_counter() - start))
    t8.join()
    print("t8: %s s" % (time.perf_counter() - start))
    t9.join()
    print("t9: %s s" % (time.perf_counter() - start))

    end_time = time.perf_counter()
    total_time = float(end_time - start_time)
    print("total time: %f s" % total_time)
    print("Estimated total time without map-reduce: %f s" % (total_time * 9))


