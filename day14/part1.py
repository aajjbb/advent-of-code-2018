VALUE = int(input())

recipes = [3, 7]
elf_recipe_idx = [0, 1]

while VALUE + 10 > len(recipes):
    new_recipe = sum(map(lambda x: recipes[x], elf_recipe_idx))
    recipes.extend((divmod(new_recipe, 10) if new_recipe >= 10 else (new_recipe,)))

    elf_recipe_idx = [(x + 1 + recipes[x]) % len(recipes) for x in elf_recipe_idx]

print(''.join([str(digit) for digit in recipes[VALUE:VALUE+10]]))