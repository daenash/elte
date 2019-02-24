# coding: utf-8
# flake8: noqa

# Logika és számításelmélet
# I. gyakorlat
#
# Készítette: Gutai Dénes

import re
from termcolor import colored

""" SEGÉDFÜGGVÉNYEK """

# Ítéletváltozók színezése
def colorize(boolean):
    if boolean:
        return colored(str(boolean), 'green')
    return colored(str(boolean), 'red')

# Ítéletváltozók megállípátása bemeneti stringből
def define_variables(formula):
    deletable_commands = ['and', 'or', 'imp', 'not', ' ', '(', ')']
    for item in deletable_commands:
        formula = formula.replace(item, ' ')
    regex = r"[\s+)(]"
    regex2 = r" +"
    formula = re.sub(regex, ' ', formula)
    formula = re.sub(regex2, ' ', formula)
    splitted = formula.split(' ')
    split_return = []
    for item in splitted:
        if item != '' and item not in split_return:
            split_return.append(item)
    return split_return

# A formula ítéletváltozóinak megváltoztatása és implikáció átírása
def change_formula(formula, variables):
    for index, item in enumerate(variables):
        change = "variables[" + str(index) + "]"
        formula = formula.replace(variables[index], change)

    formula = formula.replace("imp", "<=")
    return formula


""" SEGÉDFÜGGVÉNYEK BEZÁRÁSA """

# Logikai alapegységek: Ítéletváltozók (pl. X, R)
X = True
R = False

# és formula -> konjunkció
formulaAnd = X and R

# vagy formula -> diszjunkció
formulaOr = X or R

# negációs formula
formulaNeg = not X

# implikációs formula
formulaImp1 = X <= R

# implikációs formula másképp
formulaImp2 = not X or R

# A zárjójelezés bárhogy történhet ha a formula csak konjunkcióból vagy diszjunkcióból áll
((X and R) and X) and R

# Implikációnál jobbról balra történik a default zárójelezés
X <= (R <= (X <= R))

# Igazságtábla

# Egy tautologikus példa
### formula_to_evaluate = "(A imp (B imp C)) imp ((A imp B) imp (A imp C))"

# A formula amit ki szeretnénk értékelni
formula_to_evaluate = "(A imp (B imp C)) imp ((A imp B) imp (A imp C))"

# A formula kiértékelése
def evaluate_formula(formula_to_evaluate):

    # A formulában előforduló ítéletváltozók
    variables = define_variables(formula_to_evaluate)

    # A formula kiértékelhetővé alakítása Python nyelvben
    transformed_formula = change_formula(formula_to_evaluate, variables)

    # Bázis megadása
    def define_base(variables):

        # Hány darab ítéletváltozónk van
        count = len(variables)

        # Hány lehetséges kimenetele lehet a kiértékelésnek
        depth = 2 ** count

        # Oszlopszerű elrendezéshez használt lista
        columns = []

        # Feltöltjük az oszlopokat
        for x in range(count):
            this_column = []
            actual_bool_value = True

            # Az ismétlődés mérete
            snippet_size = depth / (2**(x+1))

            # Amíg nincs feltöltve teljesen az oszlop beszúrjuk az aktuálisan következő logikai értékeket
            while len(this_column) != depth:

                # Annyit szúrunk be, amekkora szükséges egy adott szinten
                for y in range(snippet_size):
                    this_column.append(actual_bool_value)
                actual_bool_value = not actual_bool_value

            # Az aktuális oszlopot hozzáadjuk az összes oszlop listájához
            columns.append(this_column)

        # A bázis listája
        # Az értékek, mint egy táblázat helyezkednek el benne
        base = []

        # Feltöltjük a bázist
        for x in range(depth):
            item = []
            # Az aktuális sort egy listába rendezzük
            for y in range(count):
                item.append(columns[y][x])

            # A listát a bázishoz adjuk
            base.append(item)

        # A végén visszaadjuk a bázist
        return base

    # Definiáljuk a bázist
    base = define_base(variables)

    # Fejléc
    text = ""
    for y in range(len(variables)):
        text += colored(str(variables[y]), attrs=['bold']) + "\t"

    text += colored("Eredmény", attrs=['bold'])

    print text

    # Értékek kiírása minden lehetséges esethez
    for x in base:
        text = ""
        for y in range(len(variables)):
            variables[y] = x[y]
            text += colorize(variables[y]) + "\t"

        print(text + colorize(eval(transformed_formula)))

    print

# Formula kiértékelése
print("\n" + colored("Kiértékelendő formula: ",attrs=['bold']) + colored(formula_to_evaluate,'yellow') + "\n")
evaluate_formula(formula_to_evaluate)
