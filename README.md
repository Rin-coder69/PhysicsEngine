# 🔵 Raylib Physics Engine
 
A lightweight, interactive 2D physics simulation built with [raylib](https://www.raylib.com/). Spawn circles with unique physical properties, apply forces and affectors, and connect them with a variety of spring types — all in real time.
 
---
 
## 📸 Preview
 
> *(Add a screenshot or GIF of the simulation here)*
 
---
 
## ✨ Features
 
### 🔵 Circles
 
Spawn rigid-body circles into the simulation, each with individually configurable affectors and physical properties.
 
---
 
### ⚡ Affectors
 
Affectors are forces or fields that influence circle behavior over time. They can be scoped globally (affecting all bodies) or placed as objects in the world.
 
<br>
#### 🔹 Point Affector
Acts like a gravitational body at a single position in the world. Circles within range get pulled toward that point, with force scaling inversely with distance — the closer a circle is, the stronger the pull.
 
<img width="221" alt="Point Affector" src="https://github.com/user-attachments/assets/d51db938-48e5-4057-b999-0e5d6fc4354c" />
<br>
#### 🔹 Area Affector
Defines a region that only applies its effects to bodies currently inside it. It acts as a container for other affectors rather than a force itself — for example, "only apply drag inside this box."
 
<img width="600" alt="Area Affector" src="https://github.com/user-attachments/assets/efd2e5e9-fe9d-4115-9cc1-6c17e9f1980c" />
<br>
#### 🔹 Drag Affector
Opposes a body's current velocity, simulating air or fluid resistance. The faster a circle moves, the harder drag pushes back against it, eventually causing it to coast to a stop if no other force is acting on it.
 
<br>
#### 🔹 Gravitation Affector
A global constant downward force applied to all bodies, like standard game gravity. Unlike the Point Affector, it has no origin or falloff — every circle accelerates downward at the same rate.
 
<img width="600" alt="Gravitation Affector" src="https://github.com/user-attachments/assets/99e70b4f-de94-4e80-b95a-ac145cd04d91" />
---
 
### 🌀 Springs
 
Springs connect two circles and exert forces to maintain a rest length. They can be used to link circles together and build different structures, each behaving differently depending on stiffness and damping.
 
<img width="600" alt="Springs example 1" src="https://github.com/user-attachments/assets/85facb96-ab0c-4d99-836e-a3e1435fa5bc" />
<img width="400" alt="Springs example 2" src="https://github.com/user-attachments/assets/26f228bb-56bb-489a-a11e-2faaa9b59851" />
<img width="300" alt="Springs example 3" src="https://github.com/user-attachments/assets/309cbda6-52cd-472a-be6d-ff7cda535689" />
---
 
## 🎮 Controls
 
| Input | Action |
|-------|--------|
| `Left Click` | Spawn a circle |
| `Shift + Left Click` | Create a collider |
| `Ctrl + Left Click` | Rapidly spawn many circles |
| `Hold Right Click + Release` | Create a spring between two points |
 
---
 
## 🖥️ GUI Reference
 
The **Physics Controls** panel lets you configure all properties before and during the simulation.
 
### Body
Controls the properties of the circle being spawned.
 
| Setting | Description |
|---------|-------------|
| **Type** | Sets the body type. *Dynamic* means it's fully affected by physics forces. |
| **Size** | How large the circle is. |
| **Mass** | How heavy the circle is; heavier circles are harder to move. |
| **Gravity** | How strongly this specific circle is pulled downward. |
| **Bounce** | How much the circle bounces on collision (0 = no bounce). |
| **Damping** | How quickly the circle loses velocity over time. |
| **Velocity** | The initial speed and direction the circle launches with when spawned. |
 
### Spring
Controls the properties of springs created via right click.
 
| Setting | Description |
|---------|-------------|
| **Stiffness** | How strongly the spring pulls the two circles toward the rest length. |
| **Damping** | How quickly the spring stops oscillating. |
| **Length** | The target rest length of the spring. |
| **Auto Length** | When checked, automatically sets the rest length to the distance between the two circles at creation time. |
 
### Effector
Controls the affector placed into the world.
 
| Setting | Description |
|---------|-------------|
| **Type** | Selects which effector to place (e.g. Gravitation, Drag, Point, Area). |
| **Size** | The radius of the effector's area of influence. |
| **Force** | How strongly the effector pushes or pulls circles inside it. |
| **Angle** | The direction the effector applies its force. |
 
### Global
Settings that apply to the entire simulation.
 
| Setting | Description |
|---------|-------------|
| **FPS** | Sets the target framerate of the simulation. |
| **Gravity** | Global downward gravity applied to all bodies. |
| **Spring H** | Global spring behavior constant (stiffness or rest length scale). |
 
> **Simulate** — Starts the simulation with the current settings.
 
---
