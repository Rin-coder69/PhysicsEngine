✨ Features
🔵 Circles
Spawn rigid-body circles into the simulation, each with individually configurable affectors:
⚡ Affectors
Affectors are forces or fields that influence circle behavior over time:
Point-Affector:Acts like a gravitational body at a single position in the world. Circles within range get pulled toward that point, with force typically scaling inversely with distance (closer = stronger pull).
Area Affector: Defines a region (rectangle, circle, etc.) that only applies its effects to bodies currently inside it. It's more of a container for other affectors than a force itself — e.g. "only apply wind inside this box."
Drag Affector:Opposes a body's current velocity, simulating air/fluid resistance. The faster a circle moves, the harder drag pushes back against it, eventually causing it to coast to a stop if no other force is acting on it.
Gravitation Affector: A global constant downward force applied to all bodies, like standard game gravity. Unlike Point Gravity, it has no origin or falloff — every circle just accelerates downward at the same rate.
Affectors can be scoped globally (affecting all bodies) or targeted at specific circles.



🌀 Springs
Springs connect two circles and exert forces to maintain a rest length:


🎮 Controls
InputActionLeft ClickSpawn a circleShift + Left ClickCreate a colliderCtrl + Left ClickRapidly spawn many circlesHold Right Click + ReleaseCreate a spring between two points
