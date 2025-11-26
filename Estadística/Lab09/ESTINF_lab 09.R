#==================================================================
# ESTAD?STICA - GRADO DE INGENIER?A INFORM?TICA - ULL
# PR?CTICA DE LABORATORIO 09: Principales distribuciones continuas
# Profesores de laboratorio: Carlos Gonz?lez Mart?n; Sergio Alonso
#==================================================================

#  Adem?s de las tablas estad?sticas de la asignatura, es posible realizar con
#  mayor disponibilidad los c?lculos habituales de las distribuciones estad?sticas
#  mediante algunos comandos de R

#  Un ejemplo para el caso de la uniforme continua es
#      dunif    funci?n de densidad
#      punif    funci?n de distribuci?n
#      qunif    cuantiles
#      runif    n?meros aleatorios   

library(descriptr)                #libreria para representar algunas distribuciones
library(visualize)                #libreria para representar distribuciones

# C?LCULO DE PROBABILIDADES Y CUANTILES DE VARIAS DISTRIBUCIONES CONTINUAS

#==============================================================
# 1. UNIFORME U(1,11)    distribuci?n UNIFORME__ U(a,b)
#==============================================================
dunif(3, min=1,max=11)  # valor de la funci?n de densidad en 3
visualize.unif(stat=c(3,3), a=1, b=11,  section ="bounded")

punif(3, min=1, max=11)  # funci?n de distribuci?n en 3, esto es, probabilidad entre min y 3
visualize.unif(stat=3, a=1, b=11,section ="lower")

punif(3, min=1,max=11, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 3, esto es, probabilidad entre 3 y max
visualize.unif(stat=3,  a=1, b=11, section ="upper")

punif(8, min=1,max=11)-punif(3, min=1,max=11)  #combinando dos expresiones, esto es, probabilidad entre 3 y 8
visualize.unif(stat=c(3,8), a=1, b=11,  section ="bounded")

1-(punif(8, min=1,max=11)-punif(3, min=1,max=11))  #combinando expresiones, probabilidad entre min y 3, m?s la probabilidad entre 8 y max
visualize.unif(stat=c(3,8),  a=1, b=11,  section ="tails")

qunif(0.65, min=1,max=11)  # cuantil 0.65 de la Uniforme indicada (punto cr?tico)
punif(7.5, min=1, max=11)   # la funci?n inversa, esto es, c?lculo de la probabilidad dado el punto
punif(qunif(0.65, min=1,max=11), min=1, max=11) # m?s espec?ficamente, la inversa

qunif(0.65, min=1,max=11, lower.tail=FALSE)  # cuantil 0.35 de la Uniforme indicada (punto cr?tico)
qunif(0.35, min=1, max=11) #el an?logo al anterior si la probabilidad es 1-0.65=0.35

#==============================================================
# 2. NORMAL (10,2)    distribucion NORMAL__ N(mu,sigma)
#==============================================================
dnorm(8, mean=10, sd=2)  # valor de la funci?n de densidad en 8
visualize.norm(stat=c(8,8), mu=10, sd=2,  section ="bounded")

pnorm(8, mean=10, sd=2)  # funci?n de distribuci?n en 8
visualize.norm(stat=8, mu=10, sd=2, section ="lower")

pnorm(8, mean=10, sd=2, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 8
visualize.norm(stat=8, mu=10, sd=2, section ="upper")

pnorm(12, mean=10, sd=2)-pnorm(8, mean=10, sd=2)  #combinando dos expresiones
visualize.norm(stat=c(8,12), mu=10, sd=2,  section ="bounded")

1-(pnorm(12, mean=10, sd=2)-pnorm(8, mean=10, sd=2))  #combinando expresiones
visualize.norm(stat=c(8,12), mu=10, sd=2,  section ="tails")

qnorm(0.65, mean=10, sd=2)  # cuantil 0.65 de la Normal indicada (punto cr?tico)
pnorm(10.77064, mean=10, sd=2)  # funci?n de distribuci?n en 8
visualize.norm(stat=10.77064, mu=10, sd=2, section ="lower")

qnorm(0.65, mean=10, sd=2, lower.tail=FALSE)  # cuantil 0.35 de la Normal indicada (punto cr?tico)
visualize.norm(stat=9.229359, mu=10, sd=2, section ="upper")

#Puntos cr?ticos de una distribuci?n normal(0,1)
qnorm(0.95, mean=0, sd=1)
dist_norm_perc(0.05, mean = 0, sd = 1, type = 'upper')
qnorm(0.975, mean=0, sd=1)
dist_norm_perc(0.95, mean = 0, sd = 1, type = 'both')

#Ejercicio 1. Sea Z una variable aleatoria normal est?ndar, Z~N(0, 1)
# Halla las probabilidades siguientes
# P(Z<2.15)
pnorm(2.15)
visualize.norm(stat=2.15, section ="lower")
qnorm(0.9842224)

# P(0.80<Z<1.96)
pnorm(1.96) - pnorm(0.80)
visualize.norm(stat=c(0.80,1.96), section ="bounded")

# P(-2.45<Z<1.65)
pnorm(1.65) - pnorm(-2.45)
visualize.norm(stat=c(-2.45,1.65), section ="bounded")

# P(-2.75<Z<-0.65)
# P(Z>=-1.38)
1-pnorm(-1.38)
pnorm(-1.38, lower.tail = FALSE)
# P(-2.75<Z<0)
# P(0<=Z<2.33)

# Halla el valor de Z para los casos siguientes
# F(Z) = 0.8665
qnorm(0.8665)
pnorm(qnorm(0.8665))
visualize.norm(stat=qnorm(0.8665), section ="lower")

# F(Z) = 0.9222


# F(Z) = 0.9972

# El ?rea entre -Z y Z es 0.99
qnorm((1-0.99)/2)
visualize.norm(stat=c(qnorm((1-0.99)/2),-qnorm((1-0.99)/2)), section = "bounded")

# El ?rea a la izquierda de Z es 0.05

# El ?rea a la derecha de Z 0.025

#==============================================================
# 3. CHI - CUADRADO (12)   distribuci?n CHI-CUADRADO__ chi(n)
#==============================================================
dchisq(6.15, df=12)                         # valor de la funci?n de densidad en 6.15
visualize.chisq(stat=c(6.15, 6.15), df=12, section ="bounded")

pchisq(6.15, df=12)                            # funci?n de distribucion en 6.15
visualize.chisq(6.15, df=12, section ="lower")

pchisq(6.15, df=12,lower.tail=FALSE)          # 1 - funci?n de distribucion en 6.15
visualize.chisq(6.15, df=12, section ="upper")

pchisq(10, df=12)-pchisq(3, df=12)               #combinando dos expresiones 
visualize.chisq(stat=c(3, 10), df=12, section ="bounded")

1-(pchisq(10, df=12)-pchisq(3, df=12))                  #combinando expresiones
visualize.chisq(stat=c(3, 10), df=12, section ="tails")

qchisq(0.65, df=12)  # cuantil 0.65 de la Chi Cuadrado indicada (punto cr?tico) 
qchisq(0.65,df=12, lower.tail=FALSE)  # cuantil 0.35 de la Chi Cuadrado indicada (punto cr?tico)

#Puntos cr?ticos de una chi(ji)-cuadrado con 15 g.l.
qchisq(0.95, df=15)
dist_chi_perc(0.05, 15, 'upper')
qchisq(0.025, df=15)
dist_chi_perc(0.025, 15, 'lower')
qchisq(0.975, df=15)
dist_chi_perc(0.025, 15, 'upper')

# Si la variable aleatoria X sigue una distribuci?n de una Chi Cuadrado con 25 grados de libertad, halla:
# a) P(X < 46.9)

# b) P(11.5 <= X <= 44.3)

# c) P(X > 37.7)

# d) a y b tal que P(a <= X <= b) = 0.95
# Visualizaremos primero X para comprobar su simetr?a
visualize.chisq(stat=25, df = 25, section = "lower")
# Aplicaremos que los 0.05 que deja en las colas se distribuyen al 50%
a<-qchisq(0.05/2,25, lower.tail = TRUE)
b<-qchisq(0.05/2,25, lower.tail = FALSE)
# Comprobamos
visualize.chisq(stat=c(a,b), 25, section = "bounded")

#==============================================================
# 4. T - STUDENT (30)   distribuci?n T-STUDENT__ t(n)
#==============================================================
dt(2.15, df=30)                 # valor de la funci?n de densidad en 2.15
visualize.t(stat=c(2.15,2.15), df=30, section ="bounded")

pt(2.15, df=30)                      # funci?n de distribuci?n en 2.15
visualize.t(2.15, df=30, section ="lower")

pt(2.15, df=30, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 2.15
visualize.t(2.15, df=30, section ="upper")

pt(2.5, df=30)-pt(-1.8, df=30)               #combinando dos expresiones
visualize.t(stat=c(-1.8,2.5), df=30, section ="bounded")

1-(pt(2.5, df=30)-pt(-1.8, df=30))            #combinando expresiones
visualize.t(stat=c(-1.8,2.5), df=30, section ="tails")

qt(0.65, df=30)                       # cuantil 0.65 de la t - Student indicada
qt(0.65, df=30, lower.tail=FALSE)      # cuantil 0.35 de la t - Student indicada

#Puntos cr?ticos de una T - Student con 20 g.l.
qt(0.95, df=20)
dist_t_perc(0.05, 20, 'upper')
qt(0.975, df=20)
dist_t_perc(0.95, 20, type = 'both')
qt(0.025, df=20)
dist_t_perc(0.025, 20, 'lower')
dist_t_perc(0.025, 20, 'upper')

#==============================================================
# 5. F - SNEDECOR (10,30)   distribuci?n F__ F(n1,n2)
#==============================================================
df(2.25, df1=10, df2=30)         # valor de la funci?n de densidad en 2.25
visualize.f(stat=c(2.25, 2.25), df1=10, df2=30, section ="bounded")

pf(2.25, df1=10, df2=30)         # funci?n de distribuci?n en 2.25
visualize.f(stat=2.25, df1=10, df2=30, section ="lower")
pf(2.25, df1=10, df2=30, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 2.25
visualize.f(stat=2.25, df1=10, df2=30, section ="upper") 
pf(2.25, df1=10, df2=30)-pf(0.75, df1=10, df2=30)  # combinando dos expresiones
visualize.f(stat=c(0.75, 2.25), df1=10, df2=30, section ="bounded")
1-(pf(2.25, df1=10, df2=30)-pf(0.75, df1=10, df2=30))  #combinando expresiones
visualize.f(stat=c(0.75, 2.25), df1=10, df2=30, section ="tails")

qf(0.65, df1=10, df2=30)  # cuantil 0.65 de la F - Snedecor indicada (punto cr?tico)
qf(0.65, df1=10, df2=30, lower.tail=FALSE)  # cuantil 0.35 de la F - Snedecor indicada (punto cr?tico)

#Puntos cr?ticos de una F - Snedecor con 12 y 15 g.l.
qf(0.95, df1=12, df2=15)
dist_f_perc(0.05, 12, 15, 'upper')
qf(0.975, df1=12, df2=15)  
dist_f_perc(0.025, 12, 15, 'upper')
qf(0.025, df1=12, df2=15)  
dist_f_perc(0.025, 12, 15, 'lower')

#==============================================================
# 6. Exp(2.5) distribuci?n Exponencial __Exp(lambda)
#==============================================================
dexp(0.75, rate=2.5)  # valor de la funci?n de densidad en 0.75
visualize.exp(stat=c(0.75, 0.75),theta=2.5, section ="bounded")

pexp(0.75, rate=2.5)  # funci?n de distribuci?n en 0.75
visualize.exp(stat=0.75, theta=2.5, section ="lower")
pexp(0.75, rate=2.5, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 0.75
visualize.exp(stat=0.75, theta=2.5, section ="upper")
pexp(1.8,  rate=2.5) - pexp(0.75, rate=2.5)  #combinando dos expresiones
visualize.exp(stat=c(0.75, 1.8),theta=2.5, section ="bounded")
1-(pexp(1.8,  rate=2.5) - pexp(0.75, rate=2.5))  #combinando expresiones
visualize.exp(stat=c(0.75, 1.8),theta=2.5, section ="tails")

qexp(0.65, rate=2.5)  # cuantil 0.65 de la Exponencial indicada (punto cr?tico)
qexp(0.65, rate=2.5, lower.tail=FALSE)  # cuantil 0.35 de la Exponencial indicada (punto cr?tico)

#==============================================================
# 7. Ga(10,2.5) distribuci?n Gamma __Ga(alpha, beta)
#==============================================================
dgamma(2.75, shape=10, rate=2.5)  # valor de la funci?n de densidad en 2.75
visualize.gamma(stat=c(2.75, 2.75), alpha=10,theta=2.5, section ="bounded")

pgamma(2.75, shape=10, rate=2.5)  # funci?n de distribuci?n en 2.75
pgamma(2.75, shape=10, scale=0.4)  # funci?n de distribuci?n en 2.75
visualize.gamma(stat=2.75, alpha=10,theta=2.5, section ="lower")
pgamma(2.75, shape=10, rate=2.5, lower.tail=FALSE)  # 1 - funci?n de distribuci?n en 2.75
visualize.gamma(stat=2.75, alpha=10,theta=2.5, section ="upper")
pgamma(7.4, shape=10, scale=0.4) - pgamma(2.75, shape=10, scale=0.4)  #combinando dos expresiones
visualize.gamma(stat=c(2.75, 7.4), alpha=10,theta=2.5, section ="bounded")
1-(pgamma(7.4, shape=10, scale=0.4) - pgamma(2.75, shape=10, scale=0.4))  #combinando expresiones
visualize.gamma(stat=c(2.75, 7.4),alpha=10,theta=2.5, section ="tails")

qgamma(0.38, shape=10, rate=2.5)  # cuantil 0.38 de la Gamma indicada (punto cr?tico)
qgamma(0.38, shape=10, rate=2.5, lower.tail=FALSE)  # cuantil 0.62 de la Gamma indicada (punto cr?tico)


#=====================
# FINAL DE LA PR?CTICA
#=====================

qnorm(0.9972)
