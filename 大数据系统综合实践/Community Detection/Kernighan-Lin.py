import time
import networkx as nx
from networkx.algorithms.community import kernighan_lin_bisection

from draw import draw_community_graph
from evaluate import evaluate_community_partition

file_path = "data/soc-LiveJournal1.txt"
G = nx.read_edgelist(file_path)
# G = nx.karate_club_graph()
start_time = time.time()
communities = kernighan_lin_bisection(G)
end_time = time.time()
print(communities)
print("running time:",end_time - start_time)

index = 0
partition = {}
for community in communities:
    for element in community:
        partition[element] = index
    index+=1
# print(partition)

modularity_score = evaluate_community_partition(G,partition)

print("Modularity score of the partition:", modularity_score)

# draw_community_graph(G,communities)
