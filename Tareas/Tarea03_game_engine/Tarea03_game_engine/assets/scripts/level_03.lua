-- Tabla de elementos del nivel

level = {
	-- Tabla de assets
	assets = {
		[0] = 
		{type = "texture", id = "terrain_img",	path = "./assets/img/terrain.png"},
		{type = "texture", id = "terrain_dark_img",	path = "./assets/img/terrain_dark.png"},
		{type = "texture", id = "terrain_inferno_img",	path = "./assets/img/terrain_inferno.png"},
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
		{type = "texture", id = "bg3",	path = "./assets/img/backgrounds/bg3.png"},
		{type = "texture", id = "menu1",	path = "./assets/img/menu/menu.png"},
		--Projectiles
		{type = "texture", id = "arrow",	path = "./assets/img/projectiles/arrow.png"},
		--Enemies
		{type = "texture", id = "horse_galloping",	path = "./assets/img/enemies/horse/nightmare-galloping.png"},
		{type = "texture", id = "horse_idle",	path = "./assets/img/enemies/horse/nightmare-idle.png"},
		{type = "texture", id = "hell_beast",	path = "./assets/img/enemies/hell_beast/hell-beast-idle.png"},
		{type = "texture", id = "fire_skull",	path = "./assets/img/enemies/fire_skull/fire-skull.png"},
		--Bosses
		{type = "texture", id = "demon_attack",	path = "./assets/img/bosses/flying_demon/demon-attack.png"},
		{type = "texture", id = "demon_idle",	path = "./assets/img/bosses/flying_demon/demon-idle.png"}
	},

	-- Tablas de key-action
	keyActions = {
		[0] = 
		{key = "SDLK_UP", valueMacro = 1073741906, action = "jump"},
		{key = "SDLK_RIGHT", valueMacro = 1073741903, action = "move_right"},
		{key = "SDLK_LEFT", valueMacro = 1073741904, action = "move_left"},
		{key = "SDLK_SPACE", valueMacro = 32, action = "attack"}
	},

	-- Tablas de backgrounds
	backgrounds = {
		[0] = 
		{asset = "dark_houses"},
		{asset = "bg3"},
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
		{entityType = "enemy",	id = "run",  spriteId = "mushroom_run",w = 32, h = 32, numFrames = 16, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,	srcRectY = 0},
		{entityType = "enemy",	id = "run",  spriteId = "horse_galloping",w = 144, h = 96, numFrames = 4, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0},
		--hell_beast
		{entityType = "enemy",	id = "run",  spriteId = "hell_beast",w = 55, h = 67, numFrames = 6, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0, srcRectY = 0},
		--fire_skull
		{entityType = "enemy",	id = "run",  spriteId = "fire_skull",w = 96, h = 112, numFrames = 8, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0, srcRectY = 0},
		--Boss
		{entityType = "boss",	id = "attack",  spriteId = "demon_attack",w = 240, h = 192, numFrames = 11, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0},
		{entityType = "boss",	id = "run",  spriteId = "demon_attack",w = 240, h = 192, numFrames = 11, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0},
		{entityType = "boss",	id = "idle", spriteId = "demon_idle",w = 160, h = 144, numFrames = 6, currentFrame = 01, speedRate = 15, isLoop = true, srcRectX = 0,srcRectY = 0}
	},

	-- Tabla de mapa
	map = {
		path = "./assets/levels/Level3.tmx"
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
					lifes = 3,
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
					mass = 6.0
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
					spacingRect = 60,  -- Pixels entre imagen de un mismo png
					startRect = 30,  -- Pixels antes de que empiece el png
					flip = false,
				},
				transform = {
					position = { x = 25.0, y = 32.0 },
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
		{ -- hell_beast
			tag = "enemy",
			components = {
				animation = {
					numFrames = 6,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 80,
					h = 80,
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
					assetId = "hell_beast",
					w = 55,
					h = 67,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 575.0, y = 250.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- skull
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 96,
					h = 96,
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
					assetId = "fire_skull",
					w = 96,
					h = 112,
					srcRectX = 0,
					srcRectY = 10,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 800.0, y = 250.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- hell_beast
			tag = "enemy",
			components = {
				animation = {
					numFrames = 6,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 80,
					h = 80,
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
					assetId = "hell_beast",
					w = 55,
					h = 67,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 1859.0, y = 250.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- skull
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 96,
					h = 96,
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
					assetId = "fire_skull",
					w = 96,
					h = 112,
					srcRectX = 0,
					srcRectY = 10,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 2650.0, y = 380.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},

		{ -- hell_beast
			tag = "enemy",
			components = {
				animation = {
					numFrames = 6,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 80,
					h = 80,
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
					assetId = "hell_beast",
					w = 55,
					h = 67,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 3030.0, y = 310.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- skull
			tag = "enemy",
			components = {
				animation = {
					numFrames = 8,
					currentFrame = 1,
					frameSpeedRate = 15,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 96,
					h = 96,
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
					assetId = "fire_skull",
					w = 96,
					h = 112,
					srcRectX = 0,
					srcRectY = 10,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 2667.0, y = 360.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		},
		{ -- Boss
			tag = "boss",
			components = {
				animation = {
					numFrames = 6,
					currentFrame = 1,
					frameSpeedRate = 5,
					lifes = 3,
					isLoop = true				
				},
				boxCollider = {
					w = 160,
					h = 144,
					offset = {x = 0.0, y = 0.0}
				},
				rigidbody = { 
					isStatic = false,
					mass = 5.0
				},
				script = {
					path = "./assets/scripts/boss_demon.lua"
				},
				sprite = {
					assetId = "demon_idle",
					w = 160,
					h = 144,
					srcRectX = 0,
					srcRectY = 0,
					spacingRect = 0,
					startRect = 0,
					flip = false,
				}, 
				transform = {
					position = { x = 3527.0, y = 400.0 },
					scale = { x = 1.0, y = 1.0 },
					rotation = 0.0
				}			
			}
		}
	}
}
