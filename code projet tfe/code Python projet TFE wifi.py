"""
========================
    Code projet TFE
========================
"""

"""
Ce code est le fruit de la production de mon travail. Il a été réalisé à l'ai de la documentation
de la bibliothèque plotly : https://plotly.com/python/
Je me suis également inspiré de ce qu'un compte youtube proposait sur la bibliothèque Tkinter : https://www.youtube.com/channel/UC8butISFwT-Wl7EV0hUK0BQ


==============================================================================================================
||           _                                                                      _                       ||
||          (_)                                                                    (_)                      ||
||     ___   _   _ _ _ _ _   _   _    __               _ _ _   _     ___     _ ___  _     ___     _ _ _     ||
||    | __| | | |  _   _  \ | |/ /  /  _ \   ______   /  _ _| | |  /     \  | '__/ | |  /  _  \  |  _  \    ||
||    |__ | | | | | | | | | | |\ \ |   __/  |______|  | |---  | | |  (_)  | | |    | | |  ( )  | | | | |    ||
||    |___| |_| |_| |_| |_| |_| \_\ \____|            |_|     |_|  \ ___ /  \_|    |_|  \ ___,_| |_| |_|    ||
==============================================================================================================

Nom : Simke
Prénom : Florian
Profession : Étudiant
École : HEH campus technique
Option : Bioélectronique et instrumentation

"""


""" Bibliothèques   """
""" *************   """

#Tkinter
from tkinter import *   #importer tout de chez tkinter
from PIL import ImageTk, Image  #la bibliothèque pour les images
from tkinter import messagebox  #bibliothèque pour les messages Box
from tkinter import filedialog  #bibliothèque pour le dialog de fichier
import tkinter.font as TkFont   #bibliothèque pour la taille d'écriture

#démarrage d'os pour l'ouverture de fichier en commande
import os

#plotly
import plotly.graph_objects as go   #importer plotly en tant que commande go.
from plotly.subplots import make_subplots   #importer la bibli pour plusieur graphique dans une figure

""" variables   """
""" *********   """
#Démarrage de la fenêtre
mainroot = Tk()
#Variables pour l'index dans la liste de la première et dernière valeur
st_value = 0
lst_value = 0
#Titre de mon projet
title_window = "Création d'une interface utilisateur pour afficher les courbes \n dans le monitoring de l'activité respiratoire"
#Créer les tailles de police
font_14 = TkFont.Font(size = 14, family = "Calibri")
font_16 = TkFont.Font(size = 16, family = "Calibri")
font_25 = TkFont.Font(size = 25, family = "Calibri")

clicked = StringVar()   #Variable pour la drop down box
selection_list = [      #Liste des choix possible dans la drop down box
    1,
    2,
    4,
    6,
    8
]
clicked.set(selection_list[0])  #set l'état initiale de la drop box

""" Focntions   """
""" *********   """

'''---------------------
1) Sélection fichier
---------------------'''
def openfile () :
    global filename
    filename = filedialog.askopenfilename(initialdir = "/",
    title = "Sélectionner le fichier",)
    pathway.insert(5, filename)

'''-------
2) Exit
-------'''
def exit() :
    answer_leave = messagebox.askyesno("Quitter la fenêtre", "Voulez-vous vraiment quitter la fenêtre")
    if answer_leave == 1 :
        mainroot.quit()

'''-------------
3) Open file
-------------'''
def show_file () :
    #Essais si le fichier filename existe
    try :
        filename
    #Si pas message Error
    except NameError :
        messagebox.showinfo("Afficher le fichier sélectionné", "Aucun fichier sélectionné")
    #Si filename existe et a été donné par l'utilisateur
    else :
        os.popen(filename) #Ouverture du fichier par son chemin d'accès filename

'''--------------------
4) Show range value
--------------------'''
def range_value () :
    #Essais du chemin d'accès du fichier
    try :
        filename
    #Si pas donné => message d'erreur
    except NameError :
        messagebox.showinfo("Plage de valeur dans le fichier", "Aucune donnée trouvée \n Veuillez choisir un fichier")
    #Si donné par l'utilisateur
    else :
        stValue.delete("0","end")
        lstValue.delete("0","end")
        fichier = open (filename)    #ouverture du fichier avec son chemin d'accès
        liste =[]   #création d'une liste pour stocker toutes les valeurs temps du fichier
        for colonne in fichier :    #boucle for pour prendre toutes les valeurs du fichier ligne par ligne
            line = colonne.split()[0]
            liste.append(line)  #on inclu la valeur dans la liste
            #Démarrage des variables comme global car besoin plus tard (pour les ressortir de la fct)
            global st_value
            global lst_value

            st_value = liste [0]  #donne la première valeur de la liste
            lst_value = liste[-1] #donne la dernière valeur de la liste => le chiffre étant la place (l'indexe) dans la liste, -1 est pour partir de la fin de la liste
            #remarque : -2 sera donc la deuxième valeur en partant de la fin de la liste
        stValue.insert(25, st_value)
        lstValue.insert(25, lst_value)

'''----------------
5) Use all data
----------------'''
def use_alldata () :
    #Je supprime ce qui se trouve dans les cases de choix de la plage de valeurs
    stopValue.delete("0","end")
    startValue.delete("0","end")
    #On rempli avec la range du fichier texte sélectionné
    stopValue.insert(25, lst_value)
    startValue.insert(25, st_value)

'''---------------------------
6) Split graphic
---------------------------'''

def split_graphic() :
    #Essais du chemin d'accès du fichier
    try :
        filename
    #Si pas donné par l'utilisateur
    except NameError :
        messagebox.showinfo("Création du graphique", "Aucune données disponnibles \n Veuillez renseigner un fichier de données")
    #Si le chemin est donné
    else :
        liste =[]   #création d'une liste pour stocker toutes les valeurs temps du fichier
        fichier = open(filename)
        for colonne in fichier :    #boucle for pour prendre toutes les valeurs du fichier ligne par ligne

            """ On met chaque valeur temps temporairement dans la variable line. (ligne par ligne)
                le temps étant les valeurs de la première colonne, la commande split permet de
                les récupérer en mettant la valeur de la colonne souhaitée (python démarrrant toujours à 0)
            """
            line = colonne.split()[0]   #on prend que la première colonne du fichier
            liste.append(line)  #on inclu la valeur dans la liste

        """ Traitement du fichier filename  """
        """ ******************************   """

        X=[]    #création d'une liste X
        Y=[]    #création d'une liste Y

        datagraph = open (filename)  #j'ouvre le fichier avec les données dans une variable nomée datagraph

        #Vérification si les variables entrées par l'utilisateur sont dans le fichier (qui est contenu dans la liste)
        if startValue.get() and stopValue.get() in liste :
            # On donne la valeur à la ligne de début et de fin par celles choisies par l'utilisateur
            lignestart = liste.index(startValue.get())
            lignestop = liste.index(stopValue.get())+1  # +1 car python arrête un avant (démarrant à 0 initialement)
            #Lecture du fichier dans la range choisie par l'utilisateur
            for read in datagraph.readlines() [lignestart:lignestop]:
                data = [read.strip('\n')]   #je stock ensuite chaque lignes dans la liste data en supprimant les \n grâce à la commande _.strip('ce que vous voulez supprimer')
                #la boucle for pour récupérer toutes les lignes du fichier selon la plage souhaitée par l'utilisateur
                for read in data:   #deuxième boucle for pour que dans chaque ligne je puisse récupérer la valeurs de la première et de la deuxième colonne
                    #convertion string en float pour la construction du graphique
                    stringdata = read.split()[1]
                    floatdata = int(stringdata)
                    X.append(read.split()[0])   #les valeurs temps de la première colonne sont nos X
                    Y.append(floatdata)   #les données du capteur de la deuxième colonne sont nos Y (convertis en float)
                    #remarque : python démarre toujours à 0 (correspondant à la première colonne)

            """     Choix du nbr de graphique souhaité  """
            """    ===================================  """

            if clicked.get()=="1" :     #on récupère la valeur choisie dans la drop box et on regarde si elle égale 1; 2; 4; 6 ou 8.
                graphic = go.Figure()
                # Ajout du graphique dans graphic (= go.Figure())
                graphic.add_trace(go.Scatter(
                name = "Activité musculaire",
                x=X,    #Valeurs X définies précédement
                y=Y,    #Valeurs y définies précédement
                mode="lines",   #graphique cartésien
                marker={"size": 120,
                        "color": 10,
                        "opacity": 0.6,
                        "colorscale": "Viridis",
                        },
                ))

                #Titre du graphique et légende
                graphic.update_layout(
                    title_text = "Activité du muscle abdominal respiratoir chez l'homme pendant le sommeil " + "(de " + X[1] + " à " + X[-1] + ")",
                    title_x = 0.5,
                    font=dict(
                        family="Calibri",
                        size=18,
                        color="RebeccaPurple"
                    ),
                    showlegend=True,
                    legend_title = "Légende",
                    legend_font = dict(
                        family = "Calibri",
                        size = 16,
                        color = "Black",
                    ),
                    plot_bgcolor = "white",
                )

                #Update de la ligne du graphique
                graphic.update_traces(line = dict(color = "#BF2662"))

                #Titre des axes
                graphic.update_xaxes(title_text = "Temps(HH:MM:SS)", showline = True, linecolor = "black", linewidth = 2, color = "black", )
                graphic.update_yaxes(title_text = "Amplitude (mV)", showline = True, linecolor = "black", linewidth = 2, color = "black")
                graphic.show()  #Affichage du graphique

            #range values pour l'axe X et Y
            Val_X = int(len(X))
            Val_Y = int(len(Y))

            if clicked.get()=="2" :
                # Création de la figure qui contiendra tout les graphique
                fig = make_subplots(rows=2, cols=1,
                    subplot_titles =(
                        "Plot 1 (de " + X[0] + " à " + X[int(Val_X/2)-1]+ ")",
                        "Plot 2 (de " + X[int(Val_X/2)] + " à " + X[-1] + ")",
                    )
                )
                # Ajout des graphiques
                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[0:int(Val_X/2)],
                    y=Y[0:int(Val_Y/2)]),
                    row=1, col=1,

                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/2):],
                    y=Y[int(Val_Y/2):]),
                    row=2, col=1,
                )

                #Titre du graphique et légende
                fig.update_layout(
                    title_text = "Activité du muscle abdominal respiratoir chez l'homme pendant le sommeil",
                    title_x = 0.5,
                    font=dict(
                        family="Calibri",
                        size=16,
                        color="RebeccaPurple"
                    ),
                    showlegend=True,
                    legend_title = "Légende",
                    legend_font = dict(
                        family = "Calibri",
                        size = 14,
                        color = "Black",
                    ),
                    plot_bgcolor = "white",
                    height = 1000,
                )

                #Update titre des axes
                fig.update_xaxes(title_text = "Temps(HH:MM:SS)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black")
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black")
                #===============================================================================
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black")
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black")

                fig.show()

            if clicked.get()=="4" :
                # Création de la figure qui contiendra tout les graphique
                fig = make_subplots(rows=4, cols=1,
                    subplot_titles =(
                        "Plot 1 (de " + X[0] + " à " + X[int(Val_X/4)-1] + ")",
                        "Plot 2 (de " + X[int(Val_X/4)] + " à " + X[int(Val_X/2)-1] + ")",
                        "Plot 3 (de " + X[int(Val_X/2)] + " à " + X[int(Val_X*3/4)-1] + ")",
                        "Plot 4 (de " + X[int(Val_X*3/4)] + " à " + X[-1] + ")",
                    )
                )
                # Ajout des graphiques
                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[0:int(Val_X/4)],
                    y=Y[0:int(Val_Y/4)]),
                    row=1, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/4):int(Val_X/2)],
                    y=Y[int(Val_Y/4):int(Val_Y/2)]),
                    row=2, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/2):int(Val_X*3/4)],
                    y=Y[int(Val_Y/4):int(Val_Y*3/4)]),
                    row=3, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*3/4):],
                    y=Y[int(Val_Y*3/4):]),
                    row=4, col=1
                )

                #Titre du graphique et légende
                fig.update_layout(
                    title_text = "Activité du muscle abdominal respiratoir chez l'homme pendant le sommeil",
                    title_x = 0.5,
                    font=dict(
                        family="Calibri",
                        size=16,
                        color="RebeccaPurple"
                    ),
                    showlegend=True,
                    legend_title = "Légende",
                    legend_font = dict(
                        family = "Calibri",
                        size = 14,
                        color = "Black",
                    ),
                    plot_bgcolor = "white",
                    height = 1500,
                )

                #Update titre des axes
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 4, col = 1, showline = True, linecolor = "black", color = "black",)
                #===============================================================================
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 4, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)

                fig.show()

            if clicked.get()=="6" :
                # Création de la figure qui contiendra tout les graphique
                fig = make_subplots(rows=6, cols=1,
                    subplot_titles =(
                        "Plot 1 (de " + X[0] + " à " + X[int(Val_X/6)-1] + ")",
                        "Plot 2 (de " + X[int(Val_X/6)] + " à " + X[int(Val_X/3)-1] + ")",
                        "Plot 3 (de " + X[int(Val_X/3)] + " à " + X[int(Val_X/2)-1] + ")",
                        "Plot 4 (de " + X[int(Val_X/2)] + " à " + X[int(Val_X*2/3)-1] + ")",
                        "Plot 5 (de " + X[int(Val_X*2/3)] + " à " + X[int(Val_X*5/6)-1] + ")",
                        "Plot 6 (de " + X[int(Val_X*5/6)] + " à " + X[-1] + ")",
                    )
                )
                # Ajout des graphiques
                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[0:int(Val_X/6)],
                    y=Y[0:int(Val_Y/6)]),
                    row=1, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/6):int(Val_X/3)],
                    y=Y[int(Val_Y/6):int(Val_Y/3)]),
                    row=2, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/3):int(Val_X/2)],
                    y=Y[int(Val_Y/3):int(Val_Y/2)]),
                    row=3, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/2):int(Val_X*2/3)],
                    y=Y[int(Val_Y/2):int(Val_Y*2/3)]),
                    row=4, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*2/3):int(Val_X*5/6)],
                    y=Y[int(Val_Y*2/3):int(Val_Y*5/6)]),
                    row=5, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*5/6):],
                    y=Y[int(Val_Y*5/6):]),
                    row=6, col=1
                )

                #Titre du graphique et légende
                fig.update_layout(
                    title_text = "Activité du muscle abdominal respiratoir chez l'homme pendant le sommeil",
                    title_x = 0.5,
                    font=dict(
                        family="Calibri",
                        size=16,
                        color="RebeccaPurple"
                    ),
                    showlegend=True,
                    legend_title = "Légende",
                    legend_font = dict(
                        family = "Calibri",
                        size = 14,
                        color = "Black",
                    ),
                    plot_bgcolor = "white",
                    height = 2500,
                )

                #Update titre des axes
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 4, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 5, col = 1, showline = True, linecolor = "black", color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 6, col = 1, showline = True, linecolor = "black", color = "black",)
                #===============================================================================
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 4, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 5, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 6, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)

                fig.show()


            if clicked.get()=="8" :
                # Création de la figure qui contiendra tout les graphique
                fig = make_subplots(rows=8, cols=1,
                    subplot_titles =(
                        "Plot 1 (de " + X[0] + " à " + X[int(Val_X/8)-1] + ")",
                        "Plot 2 (de " + X[int(Val_X/8)] + " à " + X[int(Val_X/4)-1] + ")",
                        "Plot 3 (de " + X[int(Val_X/4)] + " à " + X[int(Val_X*3/8)-1] + ")",
                        "Plot 4 (de " + X[int(Val_X*3/8)] + " à " + X[int(Val_X/2)-1] + ")",
                        "Plot 5 (de " + X[int(Val_X/2)] + " à " + X[int(Val_X*5/8)-1] + ")",
                        "Plot 6 (de " + X[int(Val_X*5/8)] + " à " + X[int(Val_X*3/4)-1] + ")",
                        "Plot 7 (de " + X[int(Val_X*3/4)] + " à " + X[int(Val_X*7/8)-1] + ")",
                        "Plot 8 (de " + X[int(Val_X*7/8)] + " à " + X[-1] + ")",
                    )
                )
                # Ajout des graphiques
                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[0:int(Val_X/8)],
                    y=Y[0:int(Val_Y/8)]),
                    row=1, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/8):int(Val_X/4)],
                    y=Y[int(Val_Y/8):int(Val_Y/4)]),
                    row=2, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/4):int(Val_X*3/8)],
                    y=Y[int(Val_Y/4):int(Val_Y*3/8)]),
                    row=3, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*3/8):int(Val_X/2)],
                    y=Y[int(Val_Y*3/8):int(Val_Y/2)]),
                    row=4, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X/2):int(Val_X*5/8)],
                    y=Y[int(Val_Y/2):int(Val_Y*5/8)]),
                    row=5, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*5/8):int(Val_X*3/4)],
                    y=Y[int(Val_Y*5/8):int(Val_Y*3/4)]),
                    row=6, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*3/4):int(Val_X*7/8)],
                    y=Y[int(Val_Y*3/4):int(Val_Y*7/8)]),
                    row=7, col=1
                )

                fig.add_trace(
                    go.Scatter(
                    name = "Activité du muscle",
                    x=X[int(Val_X*7/8):],
                    y=Y[int(Val_Y*7/8):]),
                    row=8, col=1
                )

                #Titre du graphique et légende
                fig.update_layout(
                    title_text = "Activité du muscle abdominal respiratoir chez l'homme pendant le sommeil",
                    title_x = 0.5,
                    font=dict(
                        family="Calibri",
                        size=16,
                        color="RebeccaPurple"
                    ),
                    showlegend=True,
                    legend_title = "Légende",
                    legend_font = dict(
                        family = "Calibri",
                        size = 14,
                        color = "Black",
                    ),
                    plot_bgcolor = "white",
                    height = 3500,
                )

                #Update titre des axes
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 4, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 5, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 6, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 7, col = 1, showline = True, linecolor = "black", color = "black",)
                fig.update_xaxes(title_text = "Temps (HH:MM:SS)", row = 8, col = 1, showline = True, linecolor = "black", color = "black",)
                #===============================================================================
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 1, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 2, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 3, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 4, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 5, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 6, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 7, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)
                fig.update_yaxes(title_text = "Amplitude (mV)", row = 8, col = 1, showline = True, linecolor = "black", linewidth = 2, color = "black",)

                fig.show()


        else :
            messagebox.showwarning("Création du graphique", "Les valeurs choisies ne sont pas contenue dans le fichier")



""" Butons   """
""" ******   """
#Création de la frame pour les boutons
frame_button = LabelFrame(mainroot, text = "Menu création du graphique", bg = "white", font = font_16, padx=80, pady=15)
frame_button.place(x=150, y = 200)

#Création des boutons
button_openfile = Button(frame_button, text = "Parcourir", fg = "#101A5F", command = openfile, font = font_14, bg = "white", width = 10)
button_openfile.grid(row = 1, column = 4, pady = 4, padx = 10, sticky = "w")
#==============================================================================================================================================
button_exit = Button(mainroot, text = "Exit", command = exit, width = 8, height = 2, font = 22, pady = 2, padx = 2, bg = "#FF5A5A")
button_exit.place(x=0, y=0)
#==============================================================================================================================================
button_showFile = Button(frame_button, text = "Ouvrir le fichier", command = show_file, font = font_14, bg = "white")
button_showFile.grid(row = 1, column = 5, pady = 4, sticky = "w")
#==============================================================================================================================================
button_selection = Button(frame_button, text = "Sélection de la plage : ", font = font_14, width = 23, command = use_alldata, bg = "white",)
button_selection.grid(row = 4, column = 1, pady = 5, padx = 4, sticky = "e")
#==============================================================================================================================================
button_rangevalue = Button(frame_button, text = "Avoir les plages de valeurs :", command = range_value, font = font_14, width = 23, bg = "white",)
button_rangevalue.grid(row = 3, column = 1, pady = 4, padx = 4)
#==============================================================================================================================================
button_creatgraphic = Button(frame_button, text = "Créer le graphique", command = split_graphic, font = font_14, width = 30, bg = "white", fg = "#BF2662")
button_creatgraphic.grid(row = 5, column = 3, columnspan = 3, pady = 4, padx = 10, sticky = "w")
#==============================================================================================================================================
#création de la drop down box
drop_selection_nbr_graphic = OptionMenu(frame_button, clicked, *selection_list)
drop_selection_nbr_graphic.config(bg = "white", width = 5, font = dict(family = "Calibri", size = font_14))
drop_selection_nbr_graphic.grid(row = 5, column = 2, pady = 4, padx = 4, ipadx = 88, ipady = 6, sticky = "w")
#==============================================================================================================================================


""" Labels   """
""" ******   """
#Création de la frame titre
frame_title = LabelFrame(mainroot, bg = "white", padx=20, pady=20)
frame_title.place(x=200, y=50)
label_title = Label(frame_title, text = title_window, font = font_25, padx=2, pady=2, bg = "white", fg = "#5EA197")
label_title.pack()

#Création des labels
#==============================================================================================================================================
startValue = Entry(frame_button, width = 25, bg = "#FFFCD6", fg = "#0F056B", borderwidth = 5, font = font_14)
startValue.insert(25, "ex : 10:20:50") #avec insert je peux écrire du texte prédéfini dans la case où l'utilisateur peut écrire
startValue.grid(row = 4, column = 2, pady = 4, padx = 10, sticky = "e")
#= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
label_a = Label(frame_button, text= " à ", font = font_14, anchor = "center", bg = "white")
label_a.grid(row = 3, column = 3, pady = 4)
label_a2 = Label(frame_button, text = " à ", font = font_14, anchor = "center", bg = "white")
label_a2.grid(row = 4, column = 3, pady = 4)
#= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
stopValue = Entry(frame_button, width = 25, bg = "#FFFCD6", fg = "#0F056B", borderwidth = 5, font = font_14)
stopValue.insert(25, "ex : 11:50:43" ) #avec insert je peux écrire du texte prédéfini dans la case où l'utilisateur peut écrire
stopValue.grid(row = 4, column = 4, columnspan = 2, pady = 4, padx = 10, sticky = "w")
#==============================================================================================================================================
frame_choisir = LabelFrame(frame_button, width = 25, bg = "white",)
frame_choisir.grid(row = 1, column = 1, pady = 4, padx = 4, sticky = "e")
label_choisir = Label(frame_choisir, text="Choisir son fichier :", font = font_14, width = 22, borderwidth = 8, bg = "white",)
label_choisir.pack()
#==============================================================================================================================================
pathway = Entry(frame_button, width = 30, bg="#C0FDFF", font=font_14, borderwidth= 5)
pathway.grid(row = 1, column = 2, columnspan = 2, pady = 4, padx = 10, sticky = "w")
#==============================================================================================================================================
stValue = Entry(frame_button, width = 25, borderwidth = 5, font = font_14, bg = "#EDFFD6")
stValue.grid(row = 3, column = 2, pady = 4, padx = 10, sticky = "e")
lstValue = Entry(frame_button, width = 25, borderwidth = 5, font = font_14, bg = "#EDFFD6")
lstValue.grid(row = 3, column = 4, columnspan = 2, pady = 4, padx = 10, sticky = "w")
#==============================================================================================================================================
frame_nbr_graphic = LabelFrame(frame_button, width = 20, bg = "white",)
frame_nbr_graphic.grid(row = 5, column = 1, pady = 4, padx = 4, sticky = "e")
label_nbr_graphic = Label(frame_nbr_graphic, text = "Nombre de graphique(s)", width = 22, borderwidth = 8, font = font_14, bg = "white",)
label_nbr_graphic.pack()

""" Spécificités de ma fenêtre  """
""" *************************   """

#mainroot.iconbitmap("G:\TFE-Stage\TFE\Codes d'essais\Codes Python\Image Bank\manga_smyley.ico")
mainroot.title("Ma Fenêtre")
mainroot.geometry("1350x600")
mainroot.configure(bg = "white")

mainroot.mainloop()
