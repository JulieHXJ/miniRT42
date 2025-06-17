/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junjun <junjun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:37:22 by junjun            #+#    #+#             */
/*   Updated: 2025/06/13 10:29:50 by junjun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


//if hit on caps (top or bottom):
// Center C of cylinder
// Direction V (normalized) of cylinder (points from bottom to top)
// Ray: P(t) = O + t * D
// Bottom center  Cb = C
// Top center  Ct = C + h * V
// Radius r
// Height h
// Solve plane-ray intersection:
// dot((P - C_plane), N) = 0
// Where:
// C_plane = cap center (Cb or Ct)
// N = normal (V or -V)
// Solve t:
// t = -dot(O - C_plane, N) / dot(D, N)
// Important: If dot(D, N) == 0, the ray is parallel to the cap and doesn't intersect.

// Check if the hit point is inside the circle (within radius):
// P_hit = O + t * D
// Check: length(P_hit - C_plane) <= r
// If true → hit is inside the cap ✅
// If false → hit is outside ❌

bool hit_cylinder_caps(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
    // Calculate intersection with top and bottom caps
    // Top cap: z = cylinder->height / 2
    // Bottom cap: z = -cylinder->height / 2
    double t_top = (cylinder->height / 2 - ray.origin.z) / ray.direction.z;
    double t_bottom = (-cylinder->height / 2 - ray.origin.z) / ray.direction.z;

    if (t_top < 0 && t_bottom < 0)
        return false; // Both caps are behind the ray

    // Check if the intersection points are within the cylinder's radius
    t_vec3 top_intersection = vec_add(ray.origin, vec_scale(ray.direction, t_top));
    t_vec3 bottom_intersection = vec_add(ray.origin, vec_scale(ray.direction, t_bottom));

    if (vec_length(vec_sub(top_intersection, cylinder->center)) <= cylinder->radius)
    {
        hit->t = t_top;
        hit->point = top_intersection;
        hit->normal = (t_vec3){0, 0, 1}; // Normal pointing up
        return true;
    }
    
    if (vec_length(vec_sub(bottom_intersection, cylinder->center)) <= cylinder->radius)
    {
        hit->t = t_bottom;
        hit->point = bottom_intersection;
        hit->normal = (t_vec3){0, 0, -1}; // Normal pointing down
        return true;
    }

    return false;
}

int hit_cylinder_cap(t_ray ray, t_vec3 center, t_vec3 normal, double radius, t_hit *hit)
{
    double denom, t;
    t_vec3 hit_point;
    
    // Check if ray and cap plane are parallel
    denom = vec_dot(normal, ray.direction);
    if (fabs(denom) < 0.0001)
        return (0);
    
    // Calculate distance to intersection with cap plane
    t = vec_dot(vec_sub(center, ray.origin), normal) / denom;
    
    // Check if intersection is behind the ray or farther than an existing hit
    if (t < 0.001 || (hit->t > 0 && hit->t < t))
        return (0);
    
    // Calculate the hit point
    hit_point = vec_add(ray.origin, vec_scale(ray.direction, t));
    
    // Check if hit point is within the cap radius
    if (vec_length(vec_sub(hit_point, center)) > radius)
        return (0); // Hit point outside cap radius
    
    // Update hit information
    hit->t = t;
    hit->point = hit_point;
    hit->normal = denom < 0 ? normal : vec_scale(normal, -1);
    
    return (1);
}



//if hit on curve sides
// Formula: The distance from the point on the ray to the cylinder axis should be equal to the radius.
// |(P(t) - C) - proj_V(P(t) - C)|² = r²
// Projection:
// Get possible values of t.:
// p(t) = O + t * D
// Let: X = O - C (vector from cylinder base to ray origin)
// a = dot(D - dot(D, V) * V, D - dot(D, V) * V)
// b = 2 * dot(D - dot(D, V) * V, X - dot(X, V) * V)
// c = dot(X - dot(X, V) * V, X - dot(X, V) * V) - r²
// a*t² + b*t + c = 0
bool hit_cylinder_sides()
{
    
}


//projection:
t_vec3 project_onto_axis(t_vec3 point, t_vec3 axis)
{
    double dot_product = vec_dot(point, axis);
    return vec_scale(axis, dot_product);
}

bool hit_cylinder(t_ray ray, t_cylinder cylinder, t_hit *hit)
{
    
}
