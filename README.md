# miniRT — A Minimal Ray Tracer  
> A 42 School project | Real-time image generation via ray tracing

## Summary

Render realistic 3D scenes by simulating the physical behavior of light — including shadows, diffuse and specular reflections — using ray tracing techniques.
## Input & Output

- **Input**: `.rt` scene description file (custom format)  
- **Output**: Graphical window (MiniLibX) displaying the rendered image

---

## Project Breakdown

### 1.Parsing & Scene Setup

- Check argument count, file name and extension  
- Acceptable elements:
  ```
  A  → Ambient light        (3 parameters)  
  C  → Camera               (4 parameters)  
  L  → Light source         (3 parameters)  
  sp → Sphere               (4 parameters)  
  pl → Plane                (4 parameters)  
  cy → Cylinder             (6 parameters)  
  co → Cone                 (6 parameters, bonus)  
  ```
- Validation:
  - RGB values: 0–255  
  - Vectors: normalized within [-1, 1]  
  - Positive diameter/height  
- Scene elements can appear in any order, separated by space, tabs, or newline separators  
- Structured scene representation for rendering

---

### 2️.Ray Tracing & Intersections

We generate a ray from the camera through each pixel of a virtual screen.

#### Viewport Setup
- Defined in front of the camera  
- Parameters: width, height, orientation (`up`, `right`, `normal`)  
- Rays are cast through each pixel

#### Object Intersections

Mathematically determine ray-object intersections:

| Object     | Method                                              |
|------------|-----------------------------------------------------|
| **Ray**    | `P(t) = origin + t * direction`                    |
| **Sphere** | Solve `|P(t) - center|² = radius²`                 |
| **Plane**  | Solve `dot(P(t) - point_on_plane, normal) = 0`     |
| **Cylinder** | Axis projection + cap test                        |
| **Cone** *(bonus)* | Parametric solution                         |

Only the closest valid intersection is retained per ray.

---

### 3️.Lighting & Shading

We calculate final pixel color based on:

#### Ambient Light
- Base illumination for the whole scene  
- `color += ambient_color * intensity`

#### Diffuse Light (Lambertian)
- Based on angle between light and surface normal  
- Blocked light = shadow  
- `intensity = max(dot(normal, light_dir), 0.0)`

#### Specular Highlights *(bonus)*
- Shiny surfaces, viewer-angle dependent  
- `intensity += pow(max(dot(reflect_dir, view_dir), 0.0), shininess)`

#### Multiple Colored Lights *(bonus)*
- Lights support RGB coloring  
- Loop through each light:
  - Cast shadow ray  
  - Accumulate diffuse/specular effects  
  - `final_color = ambient + Σ(lights)`

#### Bump Maps *(bonus)*
- Textured normal variation using PNG maps  
- Adds surface realism without changing geometry  
- Applied to sphere, plane, and cylinder

---

### 4️.Graphical Output (MiniLibX)

- Graphical window display  
- Interactive controls:
  - `ESC` or ❌ → quit  
  - Arrow keys → move camera  
  - A / D / W / X → rotate camera  
  - Scroll wheel → zoom in/out
  - R → reset camera

---

## Optional Extensions / Theory

- Vector math: `dot`, `cross`, normalization  
- Surface normals & backface culling  
- Anti-aliasing (TBD)  
- Multithreading (bonus-eligible)  
- BVH acceleration (not implemented)

---

## References & Resources

-  [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
-  [42 MiniRT Guide](https://42-cursus.gitbook.io/guide/rank-04/minirt)  
-  [Scratchapixel - Ray Tracing Intro](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/raytracing-algorithm-in-a-nutshell.html)  
-  [Cone Intersection](https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/)  
-  [The Ray Tracer Challenge](http://www.raytracerchallenge.com/)  
-  [Ray Tracing in 5 Minutes - YouTube](https://www.youtube.com/watch?v=4GGRx502-iY&ab_channel=QuantitativeBytes)  
-  Bump Mapping Resources:  
  - https://medium.com/@dbildibay/ray-tracing-adventure-part-iv-678768947371  
  - http://www.raytracerchallenge.com/bonus/texture-mapping.html  
  - https://www.irisa.fr/prive/kadi/DIIC/SDI-2-annee/Cours_RayTracing/RayTracing_Texturing.pdf  

---

## 🤝 Credits

This project was developed in collaboration with [@chrisov](https://github.com/chrisov).  
Thanks for the teamwork and discussions!
