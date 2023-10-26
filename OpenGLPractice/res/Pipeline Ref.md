# Initiation

### Context Initiation

**GLFW**

- GLFW Initiation
- GLFW Window Hint Specification
- GLFW Window Creation
- GLAD Initiation

**GLAD**

- GLAD Initiation (Load GL Functions)

### Render Settings

- Viewport
- Buffer Swap Interval
- Enable Render Functions
  - Alpha Blend
  - Cull Back
  - Depth Test (Less)

### _Set Input Callbacks_

### _GUI Initiation_

# Load Render Content

### Backstage/Default Contents

- Master Frame Buffer
- Main Camera
- Skybox
- Post Process

### Custom Contents

- Light(s) & Ambient
- Other Contents

# Main Render Loop

### Log Error from Initiation/Previous Frame

### Bind Master Frame Buffer

### Clear Buffers

### Poll Input Events & Handle Events

- _Set Shader Uniforms_

### Draw Render Contents

### Draw Skybox

### Post Process

### Blit (Custom) Master Frame Buffer to Default Frame Buffer

### Render GUI

- Custom GUI Entries
- Framerate Display

### Swap Buffer/Send Render Result to Screen

### Calculate Delta Time

# Clean Up

### Shutdown GUI Application

### Terminate GLFW Context
