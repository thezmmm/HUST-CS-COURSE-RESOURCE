
# cit-hepph
# kernighan-lin
# running time: 6.092081308364868
# Modularity score of the partition: 0.4102812020042198
# label_propagation
# running time: 7.147355556488037
# Modularity score of the partition: 0.6685685100745177
# louvain
# running time: 12.19275331497192
# Modularity score of the partition: 0.7263191475821112
# Girvan-Newman
# running time: 37.08975346597342
# Modularity score of the partition: 0.6319141219104213

# soc-LiveJournal1
# label_propagation
# running time: 1653.871600151063
# Modularity score of the partition: 0.6745613319104177
# label_propagation_cugraph
# running time: 32.015487166563
# Modularity score of the partition: 0.6695453763104177
# louvain
# running time: 3249.560459756854
# Modularity score of the partition: 0.776319856852489
# louvain_cugraph
# running time: 68.04596854560
# Modularity score of the partition: 0.772489654985407



import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
from networkx.algorithms.community import kernighan_lin_bisection


def draw_community_graph(G, communities):
    # 创建一个颜色映射
    color_map = []
    for node in G.nodes():
        for idx, community in enumerate(communities):
            if node in community:
                color_map.append(idx)  # 将社区索引作为颜色
                break

    # 使用Spring布局
    pos = nx.spring_layout(G)

    # 绘制图形
    plt.figure(figsize=(12, 8))
    nx.draw(G, pos, node_color=color_map, with_labels=True,
            node_size=500, cmap=plt.cm.rainbow, edge_color='gray', alpha=0.7)

    # 添加图例
    # unique_communities = list(set(color_map))
    # handles = [plt.Line2D([0], [0], marker='o', color='w',
    #                       markerfacecolor=plt.cm.rainbow(i / len(unique_communities)), markersize=10)
    #            for i in unique_communities]

    # plt.legend(handles=handles,
    #            labels=[f'Community {i}' for i in unique_communities],
    #            title='Communities')

    plt.title('Graph with Community Detection')
    plt.show()


# 示例使用
if __name__ == "__main__":
# 创建示例图
#     G = nx.karate_club_graph()
#     communities = kernighan_lin_bisection(G)
#     print(communities)
#     draw_community_graph(G, communities)


    # 数据
    algorithms = ['Kernighan-Lin', 'Label Propagation', 'Louvain', 'Girvan-Newman']
    running_times = [6.092081308364868, 7.147355556488037, 12.19275331497192, 37.08975346597342]
    modularity_scores = [0.4102812020042198, 0.6685685100745177, 0.7263191475821112, 0.6319141219104213]

    # 创建第一个图：运行时间的条形图
    plt.figure(figsize=(10, 6))
    plt.bar(algorithms, running_times, color='b', alpha=0.6)
    plt.xlabel('Algorithms')
    plt.ylabel('Running Time (s)', color='b')
    plt.title('Running Time of Algorithms on cit-hepph Dataset')
    plt.grid(axis='y')
    plt.show()

    # 创建第二个图：模块度得分的条形图
    plt.figure(figsize=(10, 6))
    plt.bar(algorithms, modularity_scores, color='r', alpha=0.6)
    plt.xlabel('Algorithms')
    plt.ylabel('Modularity Score', color='r')
    plt.title('Modularity Scores of Algorithms on cit-hepph Dataset')
    plt.grid(axis='y')
    plt.show()


    # 数据
    algorithms = ['Label Propagation', 'Label Propagation (cuGraph)', 'Louvain', 'Louvain (cuGraph)']
    running_times = [1653.871600151063, 32.015487166563, 3249.560459756854, 68.04596854560]
    modularity_scores = [0.6745613319104177, 0.6695453763104177, 0.776319856852489, 0.772489654985407]

    # 创建第一个图：运行时间的条形图
    plt.figure(figsize=(10, 6))
    plt.bar(algorithms, running_times, color='b', alpha=0.6)
    plt.xlabel('Algorithms')
    plt.ylabel('Running Time (s)', color='b')
    plt.title('Running Time of Algorithms on soc-LiveJournal1 Dataset')
    plt.grid(axis='y')
    plt.xticks(rotation=15)  # 旋转x轴标签
    plt.show()

    # 创建第二个图：模块度得分的条形图
    plt.figure(figsize=(10, 6))
    plt.bar(algorithms, modularity_scores, color='r', alpha=0.6)
    plt.xlabel('Algorithms')
    plt.ylabel('Modularity Score', color='r')
    plt.title('Modularity Scores of Algorithms on soc-LiveJournal1 Dataset')
    plt.grid(axis='y')
    plt.xticks(rotation=15)  # 旋转x轴标签
    plt.show()