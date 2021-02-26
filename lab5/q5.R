library(bnlearn)
library(caret)
grade <- c("AA", "AB", "BB", "BC", "CC", "CD", "DD", "F")
course.grades<-read.table( "C:/Users/THE ROCK/Desktop/Introduction_to_AI/Assignment_5/2020_bn_nb_data.txt",head=TRUE)
course.grades.net<-hc(course.grades, score = "k2")
course.grades.bn.fit <- bn.fit(course.grades.net, course.grades)

set.seed(100)
tIndex <- createDataPartition(course.grades$QP, p=0.7)$Resample1
train <- course.grades[tIndex, ]
trainda <- bn.fit(hc(train, score="k2"), train)
test <- course.grades[-tIndex, ]
predicted <- predict(trainda, node="QP", data=test)
tabletrain <- table(test$QP, predicted)
trainAcc = (tabletrain[1,1]+tabletrain[2,2])/sum(tabletrain)
print(round(cbind("Training Accuracy" =trainAcc), 4))

