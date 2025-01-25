import networkx as nx
from networkx.algorithms.community.quality import modularity

def evaluate_community_partition(graph, partition):
    """
    Evaluate the quality of a community partition using modularity.

    Parameters:
    - graph: NetworkX graph object
    - partition: Dictionary mapping nodes to communities

    Returns:
    - modularity_score: Modularity score of the partition
    """
    # Convert the partition dictionary to a list of sets
    communities = {}
    for node, community_id in partition.items():
        if community_id not in communities:
            communities[community_id] = set()
        communities[community_id].add(node)

    # Calculate modularity
    modularity_score = modularity(graph, communities.values())

    return modularity_score

# 示例用法
# G = nx.karate_club_graph()  # 创建一个示例图
# partition = {node: 0 if node < 17 else 1 for node in G.nodes()}  # 示例社区划分
# print(partition)
# modularity_score = evaluate_community_partition(G, partition)
# # modularity [-1,1] 接近1说明划分好
# print("Modularity score of the partition:", modularity_score)