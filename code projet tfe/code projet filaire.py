"""===================================================================================="""
"""                           IMPORTATION DES BIBLIOTHÈQUE                             """
"""===================================================================================="""


import matplotlib.pyplot as plt     #j'importe une bibliothèque pour contruire mon graphique


"""===================================================================================="""
"""             DEMANDE À L'UTILISATEUR DU NOM DE FICHIER/CHEMIN D'ACCÈS               """
"""===================================================================================="""

print("Vous devez d'abord me donner le nom du fichier s'il est dans le même répertoire")
print("que le fichier .py que vous venez de lancer. Ou bien donnez le chemin d'accès au fichier")
print("qui contient les données que vous souhaitez utiliser.")
print("\n")
print("Pour rappel : ")
print("*************")
print("le fichier de données est un fichier .txt et contient deux colonnes avec le temps en colonne 1")
print("et les données du capteur en colonne 2.")
print("N'oubliez pas de renseigner également l'extension du fichier lorsque je vous demande le nom de celui-ci.")
print("\n")
filename = str(input("Vous pouvez maintenant me donner le nom ou le chemin d'accès du fichier de données : "));

"""===================================================================================="""
"""                          INSTRUCTION POUR L'UTILISATEUR                            """
"""===================================================================================="""
print("Vous allez pouvoir choisir votre plage de valeur temps pour votre graphique.")

print("\n")
print("Veuillez respecter le format suivant pour votre choix : HH:MM:SS")
print("\n")
print("Où : ")
print("HH est l'heure")
print("MM sont les minutes")
print("SS sont les secondes")
print("\n")
print("En cas d'erreur fermer la fenêtre et relancer le programme")
print("\n")
print("Autre remarque : pour le choix d ela valeur de fin du temps, rajoutez 1 seconde à votre choix","\n", "car le programme démarre toujours de la position 0 et pas 1")
print("\n")
print("Veuillez également choisir dans la plage de mesure suivante", "\n")


"""===================================================================================="""
"""      Première partie : Choix de la plage de valeur temps par l'utilisateur         """
"""===================================================================================="""

fichier = open (filename)    #ouverture du fichier avec son chemin d'accès
liste =[]   #création d'une liste pour stocker toutes les valeurs temps du fichier

for colonne in fichier :    #boucle for pour prendre toutes les valeurs du fichier ligne par ligne

    """ On met chaque valeur temps temporairement dans la variable line. (ligne par ligne)
        le temps étant les valeurs de la première colonne, la commande split permet de
        les récupérer en mettant la valeur de la colonne souhaitée (python démarrrant toujours à 0)
    """
    line = colonne.split()[0]
    liste.append(line)  #on inclu la valeur dans la liste

st = liste [0]  #donne la première valeur de la liste
lst = liste[-1] #donne la dernière valeur de la liste => le chiffre étant la place (l'indexe) dans la liste, -1 est pour partir de la fin de la liste
#remarque : -2 sera donc la deuxième valeur en partant de la fin de la liste

print("les données commencent à ",st, " jusque ", lst)  #on affiche pour l'utilisateur la plage de temps d'enregistrement (au niveau temps) des données
print("\n")

""" On demande ensuite à l'utilisateur de choisir une valeur se temps de départ et de fin
    afin de prendre toutes ces valeurs et d'en faire un graphique
"""
startline = str(input("Entrer l'heure de début : "))    #ligne de début de prise de valeurs
stopline = str(input("Entrer l'heure de fin : "))       #ligne de fin de prise de valeurs

""" Il faut ensuite trouver la place de ces valeurs de temps dans la liste
    grâce à la commande liste.indexe on peut renvoyer un nombre donnant la position du choix
    de l'utilisateur dans la liste
"""
lignestart = liste.index(startline)
lignestop = liste.index(stopline)

#ces valeurs de lignestop et lignestart nous serviront plus loin dans le code
print("\n","\n")

fichier.close() #Ne pas oublier de fermer le fichier quand on a terminer


"""==========================================================================================================="""
"""      Deuxième partie : Construction du graphique avec la plage de valeurs choisie par l'utilisateur       """
"""==========================================================================================================="""

X=[]    #création d'une liste X
Y=[]    #création d'une liste Y

datagraph = open (filename)  #j'ouvre le fichier avec les données dans une variable nomée datagraph

for read in datagraph.readlines()[lignestart:lignestop]:    #la boucle for pour récupérer toutes les lignes du fichier selon la plage souhaitée par l'utilisateur
    data = [read.strip('\n')]   #je stock ensuite chaque lignes dans la liste data en supprimant les \n grâce à la commande _.strip('ce que vous voulez supprimer')

    for read in data:   #deuxième boucle for pour que dans chaque ligne je puisse récupérer la valeurs de la première et de la deuxième colonne
        print(read.split()[0],"\t",read.split()[1])
        #convertion string en float pour la construction du graphique
        stringdata = read.split()[1]
        floatdata = float(stringdata)
        X.append(read.split()[0])   #les valeurs temps de la première colonne sont nos X
        Y.append(floatdata)   #les données du capteur de la deuxième colonne sont nos Y (convertis en float)
        #remarque : python démarre toujours à 0 (correspondant à la première colonne)

""" Il est important de convertir les valeurs en Y en float et ne pas les laisser en string
    Car les valeurs en str s'afficheront à la suite de l'une et de l'autre (donnant lieu à un graphique qui ne fait que monter)
    Tandis que si ce sont des float (ou bien des int) elles se mettront correctement dans les ranges de valeurs en y et on
    ne retrouvera pas un 0.5 qui suit un 2 sur l'axe des y.
"""

"""---------------------Construction du graphique---------------------"""

""" Ici je vais juste modifier et embellir mon graphique avec plsuieur commande et paramètres que
    l'on peut donner avec plt
"""
plt.title("Données des mouvements respiratoires pendant votre sommeil", loc='center', pad='5', color='#173666', fontsize='20',)
plt.xlabel("Temps (HH:MM:SS)", color='#641480', fontsize='12', fontstyle='italic',)
plt.ylabel("Data sensor (Voltage)", color='#641480', fontsize='12', fontstyle='italic',)
plt.xticks(rotation = '90')
plt.grid(True, linestyle='--')
plt.plot(X,Y)   #fonction permettant de créer notre graphique avec les liste de données X et Y
plt.show()  #fonction pour tracer notre graphique dans une fenêtre

datagraph.close()   #on n'oublie pas de fermer le fichier ouvert
