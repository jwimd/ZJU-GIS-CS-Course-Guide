# SVM实例

## 运行结果

![2023-06-29_15-51](/home/jwimd/Study/Earth_Science_Data/Hw/Hw5/2023-06-29_15-51.png)

## 代码分析

这段代码用于支持向量机（SVM）分类任务的建模和评估。

```python
predictors = letters.columns[1:]
X_train, X_test, y_train, y_test = model_selection.train_test_split(letters[predictors], letters.letter,
                                                                    test_size=0.25, random_state=1234)
```
将数据集拆分为输入特征X和目标变量y，其中X包含除'letter'列之外的所有列，y是'letter'列。然后，使用train_test_split函数将数据集划分为训练集和测试集，其中测试集占比为0.25。

```python
C = [0.05, 0.1, 0.5, 1, 2, 5]
parameters = {'C': C}
grid_linear_svc = model_selection.GridSearchCV(estimator=svm.LinearSVC(
    dual=False), param_grid=parameters, scoring='accuracy', cv=5, verbose=1)
```
使用GridSearchCV函数进行网格搜索，以选择线性可分SVM模型中最佳的C值（正则化参数）。参数C的候选值为[0.05, 0.1, 0.5, 1, 2, 5]。使用accuracy作为评分指标进行交叉验证（cv=5），同时设置verbose参数为1以显示搜索过程的详细信息。

```python
grid_linear_svc.fit(X_train, y_train)
```
对网格搜索对象grid_linear_svc进行训练，通过拟合训练数据集X_train和y_train来搜索最佳的C值。

```python
grid_linear_svc.best_params_, grid_linear_svc.best_score_
```
返回交叉验证后得到的最佳参数值和相应的评分。

```python
pred_linear_svc = grid_linear_svc.predict(X_test)
```
使用训练好的模型对测试集X_test进行预测，将预测结果存储在pred_linear_svc中。

```python
report = metrics.classification_report(y_test, pred_linear_svc)
print(report)
```
这段代码使用classification_report函数计算模型的预测准确率，并将结果打印出来。
