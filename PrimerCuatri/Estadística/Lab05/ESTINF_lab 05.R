#==================================================================
# ESTADÍSTICA - GRADO DE INGENIERÍA INFORMÁTICA - ULL
# PRÁCTICA DE LABORATORIO 05: Estadística descriptiva de dos variables
# Profesores de laboratorio: Bencomo Domínguez Martín
#==================================================================


# TABLAS ESTADÍSTICAS DE DOS O MÁS VARIABLES

setwd("/Users/ezehdezpl/uni/2º/Estadística/Lab05")
load("HIPER200.RData")
attach(HIPER200)

# Creación de una tabla de contingencia dentro de los paquetes básicos de R

tabla1<-table(sal,cafe)
print(tabla1)               #se imprime la tabla de contingencia con frec absolutas
margin.table(tabla1,1)      #se imprime la primera marginal
margin.table(tabla1,2)      #se imprime la segunda marginal
print(prop.table(tabla1))   #se imprime la tabla de contingencia con frec relativas
print(prop.table(tabla1,1), digit=3)  #se imprime TODAS las dist. condicionadas de Y/X
print(prop.table(tabla1,2), digit=2)  #se imprime TODAS las dist. condicionadas de X/Y

# Creación de una tabla de contingencia con la libreria DescTools 

library(DescTools)
Desc(table(sal,cafe),plotit =FALSE ) #tabla de contingencia+condicionadas+marginal
# se recomienda acudir al help,  buscar Desc y luego rfrq
Desc(table(sal,cafe),rfrq="100",plotit =FALSE ) #tabla de contingencia conjunta
Desc(table(sal,cafe),rfrq="010",plotit =FALSE ) #tabla de contingencia Cafe/Sal
Desc(table(sal,cafe),rfrq="001",plotit =FALSE ) #tabla de contingencia Sal/Cafe
Desc(table(sal,cafe),rfrq="011",plotit =FALSE )
Desc(table(sal,cafe),rfrq="111",plotit =FALSE )
Desc(table(sal,cafe),rfrq="000",plotit =FALSE )

tabla2<-xtabs(~cafe+sal+genero)
print(tabla2)
f3a <- xtabs(~sal+estudios+genero, data=HIPER200)
ftable(f3a) 


# GRÁFICAS CON DOS O MÁS VARIABLES

# diagrama de rectángulos adosados y apilados
t1a<-table(sal,cafe)
print(t1a)
t1b<-table(cafe,sal)
rownames(t1a)          
colnames(t1a)<- c("no toma", "poco", "moderado", "mucho")
barplot(t1a,beside=TRUE,col=c(2,3,4),legend =rownames(t1a), sub="Cafe")
barplot(prop.table(t1a,2),beside=TRUE,sub="Cafe",col=c(2,3,4),legend =rownames(t1a))


library(lattice)

barplot(prop.table(t1a,2), beside= FALSE, col=c(2,3,4),sub="Cafe",legend.text=rownames(t1a),args.legend=list(x=6, y=0.6,  bg="white", ncol=2))

mosaicplot(t1a, col=c(2,3,4,6),main="Sal y Cafe")
mosaicplot(t1b, col=c(2,3,4),main="Cafe y Sal")

# diagrama de sectores
library(DescTools)
PlotCirc(table(sal,genero))

# Histogramas adosados y apilados

# Podemos realizar histogramas de una variable cuantitativa continua por cada nivel de una variable cualitativa (factor)
histogram(~peso|genero) 

#diagrama de cajas
boxplot(peso~estudios)  
library(ggplot2)
qplot(estudios, peso, geom="boxplot")  
bwplot(~peso|genero, data=HIPER200)

# ESTADÍSTICOS DESCRIPTIVOS DE UNA VARIABLE CONTINUA POR CADA NIVEL DE UN FACTOR más un diagrama de cajas
# se puede utilizar formulas del tipo a~b
Desc(peso~sal,HIPER200, digits=2, verbose=c(3),plotit=TRUE)

# o combinación de variables y factores
Desc(peso+talla~sal+genero,HIPER200, digits=2, verbose=c(3),plotit=TRUE)
Desc(peso~.,HIPER200, digits=2, verbose=c(3),plotit=TRUE)  # pueden salir datos excesivos
Desc(.~sal,HIPER200, digits=2, verbose=c(3),plotit=TRUE)   # pueden salir datos excesivos

#=====================
# FINAL DE LA PRÁCTICA
#=====================

