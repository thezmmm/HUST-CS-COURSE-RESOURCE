import time

import networkx as nx
import community
import matplotlib.pyplot as plt

# 创建一个示例图
from draw import draw_community_graph
from evaluate import evaluate_community_partition

file_path = "data/Cit-HepPh.txt"
G = nx.read_edgelist(file_path)
G = nx.karate_club_graph() # test Graph
print(G)

start_time = time.time()
# 使用 Louvain 方法进行社区发现
partition = community.best_partition(G)

end_time = time.time()
print(partition)

modularity_score = evaluate_community_partition(G,partition)
print("running time: ",end_time-start_time)
print("Modularity score of the partition:", modularity_score)

# # 绘制图形
# pos = nx.spring_layout(G)
# plt.figure(figsize=(10, 7))
#
# # 根据社区划分节点颜色
# cmap = plt.get_cmap('viridis', max(partition.values()) + 1)
# nx.draw_networkx_nodes(G, pos, partition.keys(), node_size=50,
#                         cmap=cmap, node_color=list(partition.values()))
#
# nx.draw_networkx_edges(G, pos, alpha=0.5)
# plt.title("Community Detection using Louvain Method")
# plt.show()