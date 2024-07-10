-- Este script contiene los niveles que tendra nuestro juego
-- En el orden que se pongan se cargaran los mismos

-- Tabla de elementos del nivel

levels = {
	-- Tabla de assets
	[0] = 
	{level_name = "level_02", level_path = "./assets/scripts/level_02.lua", terrain_name = "terrain_cave", terrain_path = "./assets/img/terrain_cave.png", terrain_elements = 64},
	{level_name = "level_03", level_path = "./assets/scripts/level_03.lua", terrain_name = "terrain_dark_img", terrain_path = "./assets/img/terrain_dark.png", terrain_elements = 11},
	{level_name = "level_01", level_path = "./assets/scripts/level_01.lua", terrain_name = "terrain_dark_img", terrain_path = "./assets/img/terrain_dark.png", terrain_elements = 11},
}

--terrain_name debe cargarse con el mismo nombre en el archivo correspondiente al nivel