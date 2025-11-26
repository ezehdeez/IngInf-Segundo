#==================================================================
# ESTAD?STICA - GRADO DE INGENIER?A INFORM?TICA - ULL
# PR?CTICA DE LABORATORIO 06: Regresi?n y Correlaci?n
# Profesores de laboratorio: Carlos Gonz?lez Mart?n; Sergio Alonso
#==================================================================

#Establecimiento del directorio de trabajo por defecto
setwd("/Users/ezehdezpl/uni/2º/Estadística/Lab06")
load("HIPER200.RData")
attach(HIPER200)

# REPRESENTACI?N GR?FICA DE VARIABLES CUANTITATIVAS
plot(peso,talla)  #diagrama de dispersi?n
plot(peso,talla, pch=20, col="red",main="diagrama de dispersi?n")  

plot(TAdias0,TAsist0, pch=20, col="red", xlab="TA Diast?lica inicial (mmHg)", ylab="TA Sist?lica inicial (mmHg)",main="diagrama de dispersi?n") 
plot(edad,TAsist0, pch=20, col="red", xlab="Edad", ylab="TA Sist?lica inicial (mmHg)",main="diagrama de dispersi?n") 

# GR?FICOS MEJORADOS, PERO OPCIONALES
library(lattice)
xyplot(TAsist0~TAdias0, type=c("p", "r"))
xyplot(peso~talla, type=c("p", "r"))

library(ggplot2)
ggplot(HIPER200, aes(x=TAdias0, y=TAsist0, shape=genero, colour=genero)) +   geom_point(size=3,shape=20) +   scale_shape_manual(values=c(1,2)) + scale_colour_brewer(palette="Set1")+ theme_bw()

ggplot(HIPER200, aes(x=TAdias0, y=TAsist0, shape=genero)) +   geom_point() + stat_smooth(method=lm, level=0.95) + theme_bw()

ggplot(HIPER200, aes(x=peso, y=talla, shape=genero, colour=genero)) +   geom_point(size=3,shape=20) +   scale_shape_manual(values=c(1,2)) + scale_colour_brewer(palette="Set1")+ theme_bw()

ggplot(HIPER200, aes(x=peso, y=talla, shape=genero)) +   geom_point() + stat_smooth(method=lm, level=0.95) + theme_bw()

ggplot(HIPER200, aes(x=TAdias0, y=TAsist0,  colour=edad)) +   geom_point() + theme_bw()

# Regresi?n lineal: recta, par?metros, gr?fico de dispersi?n con recta
reg<-lm(TAsist0~TAdias0)  # establecimiento del modelo PRIMERO Y, LUEGO X
print(reg)
summary(reg)
plot( TAdias0, TAsist0, pch=20, col="red",main="diagrama de dispersi?n")
abline(reg)
cov(TAsist0, TAdias0)   # covarianza
cor(TAsist0, TAdias0)   # correlacion de Pearson

reg<-lm(TAdias1~TAdias0)  # establecimiento del modelo
print(reg)
summary(reg)
plot( TAdias0, TAdias1, pch=20, col="red",main="diagrama de dispersi?n")
abline(reg)
cov(TAdias1, TAdias0)   # covarianza
cor(TAdias1, TAdias0)   # correlacion de Pearson


reg<-lm(TAsist0~TAdias0,data=HIPER200,subset=genero=="masculino")  # establecimiento del modelo para una subpoblaci?n
reg<-lm(TAsist0~TAdias0,data=HIPER200,subset=edad>50)              # establecimiento del modelo para una subpoblaci?n

#===============================================================
# datos del ejercicio 1, para la aplicaci?n de diversos modelos
#===============================================================
x<-c(2,3,4,4,5,5,6,7,7,9,9,10,11,11,12)
y<-c(11,12,10,13,11,9,10,7,12,8,7,3,6,5,5) 
plot(x,y, pch=20, col="red", xlim=c(0,16),ylim=c(0,12), xlab="N? de n?cleos", ylab="Tiempo de respuesta",main="diagrama de dispersi?n") 
cov(x,y)  # covarianza entre X e Y
cor(x,y)  # correlaci?n entre X e Y de Pearson


# REGRESI?N LINEAL - VARIOS MODELOS

# 1-modelo con recta
reg1<-lm(y~x)
print(reg1$coef)
summary(reg1)
abline(reg1)
xdat1<-cbind(x,y,reg1$fitted,reg1$residuals) # construimos una matriz con los datos, predichos y residuales
colnames(xdat1) <- c("n?cleos","tiempo","pred1","res1")
print(xdat1)

#pronosticos de y para ciertos valores de x=13,14 y 15
predict (reg1 ,data.frame(x=c(13,14,15)),interval ="prediction")->p_

x1<-c(13,14,15) ; y1<-c(3.78,2.98,2.17)
points(x1,y1,col="blue",pch=20)

x_<-c(2,3,4,4,5,5,6,7,9,9,11,11,12)
y_<-c(11,12,10,13,11,9,10,7,8,7,6,5,5)
plot(x_,y_, pch=20, col="red", xlim=c(0,16),ylim=c(0,12), xlab="N? de n?cleos", ylab="Tiempo de respuesta",main="diagrama de dispersi?n") 
cov(x_,y_)  # covarianza entre X e Y
cor(x_,y_)  # correlación entre X e Y


# REGRESI?N LINEAL - VARIOS MODELOS

# 1-modelo con recta
reg_<-lm(y_~x_)
print(reg_$coef)
summary(reg_)
abline(reg_)
xdat_<-cbind(x_,y_,reg_$fitted,reg_$residuals) # construimos una matriz con los datos, predichos y residuales
colnames(xdat_) <- c("n?cleos","tiempo","pred_","res_")
print(xdat_)

#pron?sticos de y para ciertos valores de x=13,14 y 15
predict (reg_ ,data.frame(x_=c(13,14,15)),interval ="prediction")

x1<-c(13,14,15) ; y1<-c(4.21,3.48,2.75)
points(x1,y1,col="blue",pch=20)


# 2-modelo parab?lico
reg2<-lm(y~x+I(x^2))
summary(reg2)
print(reg2$coef)
xdat2<-cbind(x,y,reg2$fitted,reg2$residuals)
colnames(xdat2) <- c("n?cleos","tiempo","pred2","res2")
print(xdat2)
curve(reg2$coef[1]+reg2$coef[2]*x+reg2$coef[3]*x^2, 1,15,add=TRUE, col="blue")

#pronosticos de y en ciertos valores de x=13, 14 y 15
predict (reg2 ,data.frame(x=c(13,14,15)),interval ="prediction")

# 3-modelo polin?mico de grado 3
reg3<-lm(y~x+I(x^2)+I(x^3))
aprint(reg3$coef)
summary(reg3)
xdat3<-cbind(x,y,reg3$fitted,reg3$residuals)
colnames(xdat3) <- c("n?cleos","tiempo","pred3","res3")
print(xdat3)
curve(reg3$coef[1]+reg3$coef[2]*x+reg3$coef[3]*x^2+reg3$coef[4]*x^3, 1,15,add=TRUE, col="green")

#pronosticos de y en ciertos valores de x=13, 14 y 15
predict (reg3 ,data.frame(x=c(13,14,15)),interval ="prediction")

# 4-modelo hiperb?lico  y=a+b*(1/x)
reg4<-lm(y~I(1/x)) 
summary(reg4)
curve(reg4$coef[1]+reg4$coef[2]*(1/x),add=TRUE, col="orange")

xdat4<-cbind(x,y,reg4$fitted,reg4$residuals)
colnames(xdat4) <- c("n?cleos","tiempo","pred4","res4")
print(xdat4)


#pronosticos de y en ciertos valores de x=13, 14 y 15
predict (reg4 ,data.frame(x=c(13,14,15)),interval ="prediction")

legend(13,12, c("lin","cuad","cub","hip"),col=c("black","blue","green","orange"),lty=c(1,1,1,1))

# 5-modelo logar?tmico
reg5<-lm(y~log(x))
print(reg5$coef)
summary(reg5)


plot(log(x),y, pch=20, col="red", xlab="log(N?mero de n?cleos)", ylab="Tiempo de respuesta",main="diagrama de dispersi?n") 
abline(reg5)


#=====================
# FINAL DE LA PR?CTICA
#=====================

# 1. A) como la pendiente es neg, la y es decreciente. B) 
x<-c(2,3,4,4,5,5,6,7,7,9,9,10,11,11,12)
y<-c(11,12,10,13,11,9,10,7,12,8,7,3,6,5,5)
reg_<-lm(x~y)
print(reg_$coefficients)
summary(reg_)



# 3. 
