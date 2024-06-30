-- Variable global en LUA

var_txt = "Andrey"
var_num = 22

config = {
	title = "Lab 05: Motor de videojuegos",
	fullscreen = false,
	resolution = {
		width = 800,
		height = 600
	}
}



function factorial(n)
	if n == 2 then
		return 2
	end
	return n * factorial(n - 1)
end

print("LUA -> HOLA "..var_txt)
print("LUA -> Edad "..var_num)
print("")

print("LUA -> Cubo de 3 "..pow(3, 3))
print("LUA -> Cuadrado de 4 "..pow(4, 2))
print("")