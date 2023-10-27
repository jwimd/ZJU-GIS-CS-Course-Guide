# 导入第三方模块
from sklearn import svm
import pandas as pd
from sklearn import model_selection
from sklearn import metrics

# 读取外部数据
letters = pd.read_csv(r'./letterdata.csv')

# 数据前5行
letters.head()

# 将数据拆分为训练集和测试集
predictors = letters.columns[1:]
X_train, X_test, y_train, y_test = model_selection.train_test_split(letters[predictors], letters.letter,
                                                                    test_size=0.25, random_state=1234)
# 使用网格搜索法，选择线性可分SVM“类”中的最佳C值
C = [0.05, 0.1, 0.5, 1, 2, 5]
parameters = {'C': C}
grid_linear_svc = model_selection.GridSearchCV(estimator=svm.LinearSVC(
    dual=False), param_grid=parameters, scoring='accuracy', cv=5, verbose=1)

# 模型在训练数据集上的拟合
grid_linear_svc.fit(X_train, y_train)

# 返回交叉验证后的最佳参数值
grid_linear_svc.best_params_, grid_linear_svc.best_score_
print(grid_linear_svc.best_params_, grid_linear_svc.best_score_)

# 模型在测试集上的预测
pred_linear_svc = grid_linear_svc.predict(X_test)

# 模型的预测准确率
report = metrics.classification_report(y_test, pred_linear_svc)
print(report)
