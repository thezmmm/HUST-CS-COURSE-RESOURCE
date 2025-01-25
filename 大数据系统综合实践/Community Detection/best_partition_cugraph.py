import time
import cupy as cp
import cugraph
import community as community_louvain
import networkx as nx
import matplotlib.pyplot as plt

file_path = "data/Cit-HepPh.txt"
G = nx.read_edgelist(file_path)

start_time = time.time()

# 将NetworkX图转换为cugraph图
sources = cp.array(list(G.edges())[:][0])
destinations = cp.array(list(G.edges())[:][1])
weights = cp.ones(len(sources))

cu_G = cugraph.Graph()
cu_G.add_edge_list(sources, destinations, weights)

# 使用 Louvain 方法进行社区发现
partition = cugraph.community.louvain(cu_G)

end_time = time.time()
print("running time: ", end_time - start_time)
print(partition)

# 计算模块性得分
modularity_score = cugraph.analyzeClusteringModularity(cu_G, partition)

print("Modularity score of the partition:", modularity_score)