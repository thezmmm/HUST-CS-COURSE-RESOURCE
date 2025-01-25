import time
import cudf
import cugraph
from cugraph.community import label_propagation
from evaluate import evaluate_community_partition

# 读取数据并转换为 cuDF DataFrame
file_path = "data/Cit-HepPh.txt"
edges = cudf.read_csv(file_path, delimiter=' ', header=None, names=['source', 'target'])

# 构建图
G = cugraph.Graph()
G.from_cudf_edgelist(edges, source='source', destination='target')

# 开始计时
start_time = time.time()

# 标签传播算法
labels = label_propagation(G)

# 结束计时
end_time = time.time()

# 输出结果
print(labels)
print("running time:", end_time - start_time)

# 转换标签结果为字典形式
partition = {node: label for node, label in zip(G.nodes(), labels)}

# 评估模块度分数
modularity_score = evaluate_community_partition(G, partition)

print("Modularity score of the partition:", modularity_score)
