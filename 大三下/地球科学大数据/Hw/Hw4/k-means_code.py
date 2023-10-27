import pandas as pd
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
import seaborn as sns

# 读取iris数据集
iris = pd.read_csv(r'./iris.csv')

# 查看数据集的前几行
iris.head()

# 提取出用于建模的数据集X
X = iris.drop(labels = 'Species', axis = 1)

# 构建Kmeans模型
kmeans = KMeans(n_clusters = 4)
kmeans.fit(X)

# 聚类结果标签
X['cluster'] = kmeans.labels_

# 各类频数统计
X.cluster.value_counts()

# 三个簇的簇中心
centers = kmeans.cluster_centers_

# 绘制聚类效果的散点图
sns.lmplot(x = 'Petal_Length', y = 'Petal_Width', hue = 'cluster', markers = ['^','s','o','x'], 
           data = X, fit_reg = False, scatter_kws = {'alpha':0.8}, legend_out = False)
plt.scatter(centers[:,2], centers[:,3], marker = '*', color = 'black', s = 130)
plt.xlabel('花瓣长度')
plt.ylabel('花瓣宽度')

# 图形显示
plt.show()
