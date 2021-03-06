# BouncingBall

<p align="center">
	<img src="https://media.giphy.com/media/w9CCQZFlYc2hbWuely/giphy.gif" alt="animated">
</p>  

## Description 

Two versions of a simple game simmilar to the bouncing ball game
that is invoked on facebook messenger after touching ball icon.
The first - SFML version, was written in 2019 and it was one of my first game projects.
The second is implemented on a top of a small game engine writen with modern OpenGL and GLFW. 
Game performance is the same on both implementations. There is one difference which is not counting score in OpenGL version because i didn't managed to implement
text rendering in the engine yet. 

## Engine features

- Texture class
- Sprite class
- Renderer class
- Quick entry point
- State manager
- Resource manager
- Simplicity of use


## Compilation

You will need Visual Studio 2019. Both projects provide generate_project.bat script.
Launch it for VS2019 project generation and everything should be ready for building and running.
In OpenGL version you have to manually add a reference from BouncingBall project to GameEngine project.

## References
  
- [TheCherno's OpenGL series](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 "OpenGL series")
- [TheCherno's game engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT "Game engine series")
- [docs.gl](https://docs.gl "docs.gl")
- [learnopengl.com](https://learnopengl.com "learnopengl.com")

