###################  EXERCICE 1 ###################

#1
bernoulli <- function(p) { #Fonction pour simuler bernouilli
  nbr <-runif(1) #Ceci génère un nombre aléatoire uniformément distribué sur [0;1]
  if (nbr <= p){
    res <- 1 #Si le nombre tiré est plus petit ou égal à p alors res prend 1
  } else {
    res <- 0 #Sinon res prend 0
  }
  return(res) #On retourne le res
}
testber <- bernoulli(0.7)
print(testber)
#==================================================================================================#
#2
binomial <- function(n, p){ #Fonction pour simuler binomial
  nbr<- runif(n) # Va générer n nombre entre [0;1] et le mettre dans nbr[] qui seras un tableau dans ce cas là
  compt<-0 #Compteur 
  
  for (i in 1:n) { # Pour i de 1 à n choisis en argument
    if (nbr[i]<=p) {
      compt<- compt +1 #On compte le nombre de fois que nbr[i] est plus petit ou égal à p 
    }
  }
  return(compt) #Retourne le compteur
}
testbino<-binomial(10,0.7)
print(testbino)
#==================================================================================================#
#3
geo<-function(p){ #Fonction pour simuler géométrique
  compt <- 1 #Compteur 
  while (runif(1)>p){ #Tant que le nombre généré aléatoire est supérieur à p on continue
    compt<- compt +1
  }
  return(compt) #Retourne le compteur
}

testgeo<-geo(0.7)
print(testgeo)
#==================================================================================================#
#4
uniforme<- function(k){ #Fonction uniforme1
  nbr<-round(runif(1, 1, k)) #On souhaite avoir une expérience entre 1 et k 
  return(nbr) #On retourne le nombre obtenu
}

testuni<-uniforme(2)
print(testuni)
#==================================================================================================#
#5
uniforme2 <- function(k) { #Fonction uniforme2
  nbr <- runif(k, -1, 1) # On veut à présent réaliser pour k fois entre -1 et 1, k pris en entré 
  histo <- hist(nbr, plot = FALSE)
  densite <- density(nbr)
  
  
  # Tracer l'histogramme
  plot(histo, main = "Histogramme et Densité", col = "lightblue", xlim = c(-1, 1),freq = FALSE, xlab = "Valeurs", ylab = "Densité")
  
  # Tracer la densité estimée
  lines(densite, col = "red", lwd = 2)#On utilise line car on veut une courbe et lwd=2 pour la largeur 
  
}
# Exemple d'utilisation avec k = 1000
uniforme2(1000)

#=============================================================================================

#===================Exercice 2==================#
#===================Question 1==================#

# Fonction pour simuler une variable aléatoire de Bernoulli
simulate_bernoulli <- function(p) {
  u <- runif(1)  # Générer une variable aléatoire uniforme sur [0, 1]
  if (u < 1 - p) {
    return(0)
  } else {
    return(1)
  }
}

# Paramètre de la loi de Bernoulli
p <- 0.5

cat("Prenons un paramètre p de ", p, "pour la loi de Bernoulli \n")

# Simuler une variable aléatoire de Bernoulli
result <- simulate_bernoulli(p)

cat("Variable aléatoire de Bernoulli simulée:", result, "\n")


#===================Question 2==================#

# Fonction pour simuler une variable aléatoire géométrique
simulate_geometric <- function(p) {
  u <- runif(1)  # Générer une variable aléatoire uniforme sur [0, 1)
  x <- ceiling(log(1 - u) / log(1 - p))
  return(x)
}

# Paramètre de la loi géométrique
p <- 0.3

cat("Prenons un paramètre p de ", p, "pour la loi Géométrique \n")

# Simuler une variable aléatoire géométrique
result <- simulate_geometric(p)

cat("Variable aléatoire géométrique simulée:", result, "\n")


#===================Question 3==================#

# Fonction pour simuler une variable aléatoire de Poisson
simulate_poisson <- function(lambda) {
  u <- runif(1)  # Générer une variable aléatoire uniforme sur [0, 1)
  x <- 0
  F <- exp(-lambda)
  while (u >= F) {
    x <- x + 1
    F <- F + exp(-lambda) * (lambda^x) / factorial(x)
  }
  return(x)
}

# Paramètre de la loi de Poisson
lambda <- 2.5

cat("Prenons un paramètre lambda de ", lambda, "pour la loi de Poisson \n")

# Simuler une variable aléatoire de Poisson
result <- simulate_poisson(lambda)

cat("Variable aléatoire de Poisson simulée:", result, "\n")

#===================Question 4==================#

# Fonction pour simuler une variable aléatoire exponentielle
simulate_exponential <- function(lambda) {
  u <- runif(1)  # Générer une variable aléatoire uniforme sur [0, 1)
  x <- -log(1 - u) / lambda
  return(x)
}

# Paramètre de la loi exponentielle
lambda <- 0.5

cat("Prenons un paramètre lambda de ", lambda, "pour la loi exponentielle \n")

# Simuler une variable aléatoire exponentielle
result <- simulate_exponential(lambda)

cat("Variable aléatoire exponentielle simulée:", result, "\n")


###################  EXERCICE 3 ###################
#Q1
N<-100 # Nombre de variables à sumuler
Xn<-runif(N) # Xn se présente comme un tableau dans lequel une case est un runif()
S<-cumsum(Xn) # Permet de faire une somme cumulative des Xn
m<-mean(Xn) #Fonction qui permet de calculer la moyenne de Xn
Sn_n<-S/1:N 
# Tracer les courbes sur un même graphe
plot(1:N, Sn_n, type = "l", xlab = "n", ylab = "Sn/n", main = "Loi des grands nombres")
abline(h = m, col = "blue", lty = 1) #On utilise abline car on veut une ligne droite, h pour une ligne horizontale et lty=1 pour une ligne pleine
#==================================================================================================#
#Q2
N<-100 # Nombre de variables à sumuler
lambda<-10
Xn<-rexp(N, lambda) #La fonction rexp(N,lambda) permet de lancer N fois une loi exponentielle de paramètre lambda
S<-cumsum(Xn)
m<-mean(Xn)
Sn_n<-S/1:N
plot(1:N, Sn_n, type = "l", xlab = "n", ylab = "Sn/n", main = "Loi expo")
abline(h = m, col = "blue", lty = 1) #On utilise abline car on veut une ligne droite, h pour une ligne horizontale et lty=1 pour une ligne pleine
#==================================================================================================#
# Q3
N <- 1000
# Fonction de densité
f_density <- function(x) { #Fonction de densité de l'énoncé
  if (x >= 0 & x <= 1) {
    return(2 * x)
  } else {
    return(0)
  }
}
# Fonction inverse de la fonction de répartition
inverse_cdf <- function(u) {
  sqrt(u)
}
# Générer des variables aléatoires en inversant la fonction de répartition
Xn <- inverse_cdf(runif(N))
S <- cumsum(Xn)
m <- mean(Xn)
Sn_n <- S/1:N

# Tracer les courbes sur un même graphe
plot(1:N, Sn_n, type = "l", xlab = "n", ylab = "Sn/n", main = "Variables aléatoires avec densité")
abline(h = m, col = "blue", lty = 1) #On utilise abline car on veut une ligne droite, h pour une ligne horizontale et lty=1 pour une ligne pleine
#==================================================================================================#
#=====================Exercice 4========================#
#=====================Question 1========================#
#
#
# Paramètres
n <- 1000    # Nombre d'itérations
Zn <- numeric(n)
sigma <- sqrt(1/12)   # Écart-type de la distribution uniforme
m <- 1/2       # Moyenne de la distribution uniforme

# Fonction pour calculer la suite Zn avec le TCL
calculate_Zn <- function(n, sigma, m) {
  for (i in 1:n) {
    Xn <- runif(n)
    Sn <- cumsum(Xn)
    Zn[i] <- (sqrt(i) / sigma) * ((Sn[i] / i) - m)
  }
  return(Zn)
}


hist(calculate_Zn(n,sigma,m),breaks = 30, prob = TRUE, col = 'lightblue')
curve(exp(-x^2/2)/sqrt(2*pi), add = TRUE, col = 'blue', lty = 2, lwd = 2)  # Ajout de la densité de la loi gaussienne en bleu

#
#
#=====================Exercice 4 question 2====================#
#
#
#
# Paramètres
lambda<-10
n <- 1000    # Nombre d'itérations
Zn <- numeric(n)
sigma <- sqrt(1/lambda^2)   # Écart-type de la distribution uniforme
m <- 1/lambda       # Moyenne de la distribution uniforme



#La fonction rexp(N,lambda) permet de lancer N fois une loi exponentielle de paramètre lambda
# Fonction pour calculer la suite Zn avec le TCL
calculate_Zn_expo <- function(n, sigma, m) {
  for (i in 1:n) {
    Xn<-rexp(n, lambda)
    Sn <- cumsum(Xn)
    Zn[i] <- (sqrt(i) / sigma) * ((Sn[i] / i) - m)
  }
  return(Zn)
}



hist(calculate_Zn_expo(n,sigma,m),breaks = 30, prob = TRUE, col = 'lightblue')
curve(exp(-x^2/2)/sqrt(2*pi), add = TRUE, col = 'blue', lty = 2, lwd = 2)  # Ajout de la densité de la loi gaussienne en bleu


#=====================Exercice 4 question 3====================#
#
#
#
#


# Nombre d'échantillons à générer
n <- 1000

#Calcul de la suite de la 3ème question
calculate_Zn_3 <- function(n) {
  for (i in 1:n) {
    val <- runif(n)
    Xn <- sqrt(val)
    m <- mean(Xn) # Calcul de l'écart type
    sigma <- mean(Xn^2)-m^2 #Calcul de la moyenne de distribution
    Sn <- cumsum(Xn)
    Zn[i] <- (sqrt(i) / sigma) * ((Sn[i] / i) - m)
  }
  return(Zn)
}

hist(calculate_Zn_3(n),breaks = 30, prob = TRUE, col = 'lightblue')
curve(exp(-x^2/2)/sqrt(2*pi), add = TRUE, col = 'blue', lty = 2, lwd = 2)  # Ajout de la densité de la loi gaussienne en bleu

#===========================================================================================#


#==============================================================================================
#==============================================================================================

#======================Exercice 5 - Box-Muller Partie 1 : Box-Muller & TCL=================#
library(ggplot2)
# On définit le nombre d'échantillons à générer
n <- 1000

# On initialise les X et Y pour stocker les échantillons générés par la méthode de Box-Muller
X <- numeric(n)
Y <- numeric(n)

# On utilise la formule pour Box-Muller donnée dans l'exercice
for (i in 1:n) {
  U <- runif(1)
  V <- runif(1)
  R <- sqrt(-2 * log(U))
  theta <- 2 * pi * V
  X[i] <- R * cos(theta)
  Y[i] <- R * sin(theta)
}
# Pour chaque itération, on génère une valeur aléatoire de u et v

# On compare les échantillons générés par la méthode de Box-Muller avec les autres méthodes
label_boxmuller <- rep("Box-Muller", n)
df_boxmuller <- data.frame(samples = c(X, Y), label = label_boxmuller)

# Conversion de la colonne 'samples' en numérique
df_boxmuller$samples <- as.numeric(df_boxmuller$samples)


# FONCTION TCL
# Paramètres
n <- 2000   # Nombre d'itérations, curieusement il faut un n qui est double
#de celui du n de box-muller : cela semble être soit un oubli, soit une curiosité lié à ggplot.
sigma <- sqrt(1/12)   # Écart-type de la distribution normale
m <- 1/2      # Moyenne de la distribution normale

Zn <- numeric(n)

# Fonction pour calculer la suite Zn avec le TCL
calculate_Zn <- function(n, sigma, m) {
  for (i in 1:n) {
    Xn <- runif(n)
    Sn <- cumsum(Xn)
    Zn[i] <- (sqrt(i) / sigma) * ((Sn[i] / i) - m)
  }
  return(Zn)
}



# Créer le dataframe pour la méthode TCL
label_tcl <- rep("TCL", n)
df_tcl <- data.frame(samples = unlist(calculate_Zn(n, sigma, m)), label = label_tcl)

# Conversion de la colonne 'samples' en numérique
df_tcl$samples <- as.numeric(df_tcl$samples)


#On combine les 2 jeux de données pour pouvoir comparer sur le graph
df_combined <- rbind(df_boxmuller, df_tcl)


#Tracé de l'histogramme, les fréquences en ordonnées, les valeurs en abscisses
# bin est le nombre de bandes choisies (= la précision, on peut augmenter son nombre pour dilluer les fréquences des valeurs
#ou diminuer son nombre pour avoir une idée de où sont centrées les valeurs

# Tracé de l'histogramme avec ggplot2
ggplot(df_combined, aes(x = samples, fill = label)) +
  geom_histogram(position = "identity", alpha = 0.7, bins = 30, color = "white") + theme_minimal() +
  labs(title = "Comparaison de la Loi Normale (0,1) : Box-Muller et TCL avec rnorm",
       x = "Valeurs",
       y = "Fréquences") +
  scale_fill_manual(values = c("Box-Muller" = "darkblue", "TCL" = "coral")) +
  theme(legend.position = "right")

#On voit donc par la superposition des 2 graphiques,que la méthode box muller semble être proche
#des méthodes utilisées précédemment. En effet, peut importe le nombre de simulation on ne distingue
#pas de différence majeure entre les 2 méthodes les fréquences sont proches les unes des autres.

#Une augmentation du bin (~>40) va accentuer les différences entre les 2 méthodes, ce qui semble logique
#car l'on travaille avec des approximations tandis qu'un faible nombre montre en toute logique
#une différence faible

#On peut aussi jouer avec l'échantillon pour masquer les différences entre box muller et les autres méthodes
#Sur des gros échantillons ( n > 10 000) la différence de méthodes est alors quasi-invisible.


#==============================================================================================

#==============================================================================================
#==============================================================================================
#=====================Exercice 5 Part 2 : Box-Muller et Loi exponentielle===============#
library(ggplot2)
# On définit le nombre d'échantillons à générer
n <- 1000

# On initialise les X et Y pour stocker les échantillons générés par la méthode de Box-Muller
X <- numeric(n)
Y <- numeric(n)

# On utilise la formule pour Box-Muller données dans l'exercice
for (i in 1:n) {
  U <- runif(1)
  V <- runif(1)
  R <- sqrt(-2 * log(U))
  theta <- 2 * pi * V
  X[i] <- R * cos(theta)
  Y[i] <- R * sin(theta)
}
# Pour chaque itération, on génère une valeur aléatoire de u et v

# On compare les échantillons générés par la méthode de Box-Muller avec les autres méthodes
label_boxmuller <- rep("Box-Muller", n)
df_boxmuller <- data.frame(samples = c(X, Y), label = label_boxmuller)

# Conversion de la colonne 'samples' en numérique
df_boxmuller$samples <- as.numeric(df_boxmuller$samples)


#LOI EXPONENTIELLE & TCL
# Paramètres
lambda<-10
n <- 2000   # Nombre d'itérations
Zn <- numeric(n)
sigma <- sqrt(1/lambda^2)   # Écart-type de la distribution uniforme
m <- 1/lambda       # Moyenne de la distribution uniforme



#La fonction rexp(N,lambda) permet de lancer N fois une loi exponentielle de paramètre lambda
# Fonction pour calculer la suite Zn avec le TCL
calculate_Zn_expo <- function(n, sigma, m) {
  for (i in 1:n) {
    Xn<-rexp(2000, lambda)
    Sn <- cumsum(Xn)
    Zn[i] <- (sqrt(i) / sigma) * ((Sn[i] / i) - m)
  }
  return(Zn)
}



# Création du dataframe pour les simulations TCL
label_tcl <- rep("TCL",n)
df_tcl <- data.frame(samples = as.vector(calculate_Zn_expo(n, sigma, m)), label = label_tcl)

# Tracé de l'histogramme avec ggplot2
df_combined <- rbind(df_boxmuller, df_tcl)

ggplot(df_combined, aes(x = samples, fill = label)) +
  geom_histogram(position = "identity", alpha = 0.7, bins = 30, color = "white") + theme_minimal() +
  labs(title = "N(0,1) : Box-Muller vs. TCL exponentielle",
       x = "Valeurs",
       y = "Fréquences") +
  scale_fill_manual(values = c("Box-Muller" = "darkblue", "TCL" = "lightblue")) +
  theme(legend.position = "right")

#==============================================================================================
#==============================================================================================
