-- Tabla de elementos del nivel

level = {
	-- Tabla de assets
	assets = {
		[0] = 
		{type = "texture", id = "terrain_img",	path = "./assets/img/terrain.png"},
		{type = "texture", id = "terrain_dark_img",	path = "./assets/img/terrain_dark.png"},
		{type = "texture", id = "frog_idle",	path = "./assets/img/frog_idle.png"},
		{type = "texture", id = "frog_run",		path = "./assets/img/frog_run.png"},
		{type = "texture", id = "frog_fall",	path = "./assets/img/frog_fall.png"},
		{type = "texture", id = "frog_jump",	path = "./assets/img/frog_jump.png"},
		{type = "texture", id = "mushroom_run",	path = "./assets/img/mushroom_run.png"},
		--Player
		{type = "texture", id = "archer_attack",path = "./assets/img/players/archer/archer_attack.png"},
		{type = "texture", id = "archer_death",	path = "./assets/img/players/archer/archer_death.png"},
		{type = "texture", id = "archer_fall",	path = "./assets/img/players/archer/archer_fall.png"},
		{type = "texture", id = "archer_gethit",path = "./assets/img/players/archer/archer_gethit.png"},
		{type = "texture", id = "archer_idle",	path = "./assets/img/players/archer/archer_idle.png"},
		{type = "texture", id = "archer_jump",	path = "./assets/img/players/archer/archer_jump.png"},
		{type = "texture", id = "archer_run",	path = "./assets/img/players/archer/archer_run.png"},
		--Backgrounds
		{type = "texture", id = "dark_sky",	path = "./assets/img/backgrounds/dark_sky.png"},
		{type = "texture", id = "dark_houses",	path = "./assets/img/backgrounds/dark_houses.png"},
		--Projectiles
		{type = "texture", id = "arrow",	path = "./assets/img/projectiles/arrow.png"}
	},

	-- Tablas de key-action
	keyActions = {
		[0] = 
		{key = "SDLK_UP", valueMacro = 1073741906, action = "jump"},
		{key = "SDLK_RIGHT", valueMacro = 1073741903, action = "move_right"},
		{key = "SDLK_LEFT", valueMacro = 1073741904, action = "move_left"},
		{key = "SDLK_SPACE", valueMacro = 32, action = "attack"}
	},

	-- Tabla de animaciones
	animations = {
		[0] = 
		--Archer
		{entityType = "player", id = "idle", spriteId = "archer_idle", w = 40, h = 40, numFrames = 10, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "fall", spriteId = "archer_fall", w = 40, h = 40, numFrames = 02, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 26},
		{entityType = "player", id = "jump", spriteId = "archer_jump", w = 40, h = 40, numFrames = 02, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "run",  spriteId = "archer_run",  w = 40, h = 40, numFrames = 08, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		{entityType = "player", id = "attack",spriteId ="archer_attack",w =40, h = 40, numFrames = 06, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 30, srcRectY = 30},
		--Horse
		{entityType = "enemy",	id = "run",  spriteId = "mushroom_run",w = 32, h = 32, numFrames = 16, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,	srcRectY = 0}
	},

	-- Tabla de mapa
	map = {
		path = "./assets/levels/Level1.tmx"
	},

	-- Tabla de entidades
	entities = {
		[0] = 
		{ -- Player
			tag = "player",
			components = {
				animation = {
					numFrames = 10,
					currentFrame = 1,
					frameSpeedRate = 15,
					isLoop = true				
				},
				boxCollider = {
					w = 40,
					h = 40,
					offset = {x = 0.0, y = 0.0}
				},
				cameraFollow = {},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/player.lua"
				},
				sprite = {
					assetId = "archer_idle",
					w = 40,
					h = 40,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 60
				},
				transform = {
					position = { x = 17.0, y = 32.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				},
				projectile = {
					assetId = "arrow",
					speedProjectile = 400,
					mass = 0.5,
					width = 24,
					height = 5
				}
			}
		},
		{ -- Enemy
			tag = "enemy",
			components = {
				animation = {
					numFrames = 16,
					currentFrame = 1,
					frameSpeedRate = 15,
					isLoop = true				
				},
				boxCollider = {
					w = 32,
					h = 32,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/enemy.lua"
				},
				sprite = {
					assetId = "mushroom_run",
					w = 32,
					h = 32,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 0
				}, 
				transform = {
					position = { x = 360.0, y = 320.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		}
	}
}
