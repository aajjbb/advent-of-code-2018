VALUE = str(input())

ans = 0
recipes = '37'
elf_recipe_idx = [0, 1]

while not VALUE in str(recipes[-7:]):
    new_recipe = sum(map(lambda x: int(recipes[x]), elf_recipe_idx))
    recipes += str(new_recipe)
    elf_recipe_idx = [(x + 1 + int(recipes[x])) % len(recipes) for x in elf_recipe_idx]

print(recipes.index(VALUE))