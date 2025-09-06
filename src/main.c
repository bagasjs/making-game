#include "vendors/glad.h"
#include <GLFW/glfw3.h>
#include "cutils.h"
#include "vendors/stb_image.h"

#define GM_IMPLEMENTATION
#include "gm.h"
#undef GM_IMPLEMENTATION

typedef struct Vertex {
    Vec3 pos;
    Vec4 color;
    Vec2 tex_coords;
} Vertex;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int window_width = WINDOW_WIDTH;
int window_height = WINDOW_HEIGHT;
float last_x = (float)WINDOW_WIDTH/2, last_y = (float)WINDOW_HEIGHT/2;
float yaw = 0.0f, pitch = 0.0f;

void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;
    last_x = xpos;
    last_y = ypos;
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}

int main(void)
{
    if(!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Isometric Minecraft", NULL, NULL);
    bool cursor_disabled_mode = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    if(!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    Vertex vertices[] = {
        { .pos = { -0.5f, -0.5f, -0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { +0.5f, -0.5f, -0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { +0.5f, +0.5f, -0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { -0.5f, +0.5f, -0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 

        { .pos = { -0.5f, -0.5f, +0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { +0.5f, -0.5f, +0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { +0.5f, +0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { -0.5f, +0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 

        { .pos = { -0.5f, +0.5f, +0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { -0.5f, +0.5f, -0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { -0.5f, -0.5f, -0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { -0.5f, -0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 

        { .pos = { +0.5f, +0.5f, +0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { +0.5f, +0.5f, -0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { +0.5f, -0.5f, -0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { +0.5f, -0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 

        { .pos = { -0.5f, -0.5f, -0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { +0.5f, -0.5f, -0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { +0.5f, -0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { -0.5f, -0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 

        { .pos = { -0.5f, +0.5f, -0.5f }, .color = { 0.0f, 1.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 0.0f, } }, 
        { .pos = { +0.5f, +0.5f, -0.5f }, .color = { 0.0f, 0.0f, 1.0f, 1.0f }, .tex_coords = { 1.0f, 0.0f, } }, 
        { .pos = { +0.5f, +0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 1.0f, 1.0f, } }, 
        { .pos = { -0.5f, +0.5f, +0.5f }, .color = { 1.0f, 0.0f, 0.0f, 1.0f }, .tex_coords = { 0.0f, 1.0f, } }, 
    };

    // Indices are part of vao
    uint32_t indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20,
    };
    glEnable(GL_DEPTH_TEST);

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

    GLuint ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    StringBuilder sb = {0};
    int  success;
    char info_log[512];

    if(!read_entire_file("assets/shaders/basic.vert", &sb)) return -1;
    GLuint vsmod = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsmod, 1, (const char**)&sb.items, NULL);
    glCompileShader(vsmod);
    glGetShaderiv(vsmod, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vsmod, sizeof(info_log), NULL, info_log);
        fprintf(stderr, "ERROR: vertex shader compilation failed: %s\n", info_log);
        return -1;
    }

    sb.count = 0;
    if(!read_entire_file("assets/shaders/basic.frag", &sb)) return -1;
    GLuint fsmod = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsmod, 1, (const char**)&sb.items, NULL);
    glCompileShader(fsmod);
    glGetShaderiv(fsmod, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fsmod, sizeof(info_log), NULL, info_log);
        fprintf(stderr, "ERROR: fragment shader compilation failed: %s\n", info_log);
        return -1;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vsmod);
    glAttachShader(shader_program, fsmod);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader_program, sizeof(info_log), NULL, info_log);
        fprintf(stderr, "ERROR: shader program linking failed: %s\n", info_log);
        return -1;
    }

    glUseProgram(shader_program);
    glDeleteShader(vsmod);
    glDeleteShader(fsmod);
    stbi_set_flip_vertically_on_load(true);  
    int width, height, nchannels;
    uint8_t *data = stbi_load("assets/images/brick-wall.jpg", &width, &height, &nchannels, 0);
    if(!data) return -1;
    GLenum internal_format = nchannels == 4 ? GL_RGBA  : GL_RGB;
    GLenum source_format   = nchannels == 4 ? GL_RGBA  : GL_RGB;
    printf("Loaded image with %d channels\n", nchannels);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, source_format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    const char *u_name = "u_tex";
    int loc = glGetUniformLocation(shader_program, u_name);
    if(loc < 0) {
        fprintf(stderr, "Failed to get uniform with name: %s\n", u_name);
        return -1;
    }
    glUniform1i(loc, 0);

    Vec3 cube_positions[] = {
        vec3( 0.0f,  0.0f,  0.0f), 
        vec3( 2.0f,  5.0f, -15.0f), 
        vec3(-1.5f, -2.2f, -2.5f),  
        vec3(-3.8f, -2.0f, -12.3f),  
        vec3( 2.4f, -0.4f, -3.5f),  
        vec3(-1.7f,  3.0f, -7.5f),  
        vec3( 1.3f, -2.0f, -2.5f),  
        vec3( 1.5f,  2.0f, -2.5f), 
        vec3( 1.5f,  0.2f, -1.5f), 
        vec3(-1.3f,  1.0f, -1.5f)  
    };

    float delta_time = 0.0f;
    float last_frame = 0.0f;
    Vec3 camera_pos = vec3(0.0f, 0.0f, 3.0f);
    Vec3 camera_front = vec3(0.0f, 0.0f, -1.0f);
    Vec3 world_up_dir = vec3(0.0f, 1.0f, 0.0f);
    while(!glfwWindowShouldClose(window)) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        int current_window_width, current_window_height;
        glfwGetWindowSize(window, &current_window_width, &current_window_height);
        if(current_window_width != window_width || current_window_height != window_height) {
            glViewport(0, 0, current_window_width, current_window_height);
            window_width = current_window_width;
            window_height = current_window_height;
        }

        const float camera_speed = 2.5f * delta_time;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if(cursor_disabled_mode) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetCursorPosCallback(window, NULL);
            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, cursor_pos_callback);
            }
        }
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
            camera_pos = vec3_add(camera_pos, vec3_mul_scalar(camera_front, camera_speed));
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
            camera_pos = vec3_sub(camera_pos, vec3_mul_scalar(camera_front, camera_speed));
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
            camera_pos = vec3_sub(camera_pos, vec3_mul_scalar(vec3_normalize(vec3_cross(camera_front, world_up_dir)), camera_speed));
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
            camera_pos = vec3_add(camera_pos, vec3_mul_scalar(vec3_normalize(vec3_cross(camera_front, world_up_dir)), camera_speed));
        Vec3 direction = vec3(
            cos(DEG2RAD(yaw)) * cos(DEG2RAD(pitch)),
            sin(DEG2RAD(pitch)),
            sin(DEG2RAD(yaw)) * cos(DEG2RAD(pitch)));
        camera_front = vec3_normalize(direction);
        Mat4 view  = mat4_look_at(camera_pos, vec3_add(camera_pos, camera_front), world_up_dir);
        u_name = "u_view";

        loc = glGetUniformLocation(shader_program, u_name);
        if(loc < 0) {
            fprintf(stderr, "Failed to get uniform with name: %s\n", u_name);
            return -1;
        }
        glUniformMatrix4fv(loc, 1, GL_FALSE, view.data);

        Mat4 proj  = proj = mat4_perspective(DEG2RAD(45.0f), (float)current_window_width/(float)current_window_height, 0.1f, 100.0f);
        u_name = "u_proj";
        loc = glGetUniformLocation(shader_program, u_name);
        if(loc < 0) {
            fprintf(stderr, "Failed to get uniform with name: %s\n", u_name);
            return -1;
        }
        glUniformMatrix4fv(loc, 1, GL_FALSE, proj.data);

        for(int i = 0; i < ARRAY_LEN(cube_positions); ++i) {
            Mat4 model = mat4_eye(1.0f);
            model = mat4_translate(model, cube_positions[i]);
            u_name = "u_model";
            loc = glGetUniformLocation(shader_program, u_name);
            if(loc < 0) {
                fprintf(stderr, "Failed to get uniform with name: %s\n", u_name);
                return -1;
            }
            glUniformMatrix4fv(loc, 1, GL_FALSE, model.data);
            glDrawElements(GL_TRIANGLES, ARRAY_LEN(indices), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
