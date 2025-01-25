import time
import networkx as nx
from networkx.algorithms.community import louvain_communities

from draw import draw_community_graph
from evaluate import evaluate_community_partition

file_path = "data/Cit-HepPh.txt"
G = nx.read_edgelist(file_path)
# G = nx.karate_club_graph()
start_time = time.time()
communities = louvain_communities(G)
end_time = time.time()
print(communities)

index = 0
partition = {}
for community in communities:
    for element in community:
        partition[element] = index
    index+=1
# print(partition)

modularity_score = evaluate_community_partition(G,partition)
print("running time:",end_time - start_time)
print("Modularity score of the partition:", modularity_score)

# draw_community_graph(G,communities)
