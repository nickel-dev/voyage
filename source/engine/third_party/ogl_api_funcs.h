// basics
X(glBlendFuncSeparate, void, (GLenum srcRGB,GLenum dstRGB,GLenum srcAlpha,GLenum dstAlpha))
X(glBlendEquation, void, (GLenum mode))
X(glBlendEquationSeparate, void, (GLenum modeRGB, GLenum modeAlpha))

// buffers
X(glGenBuffers, void, (GLsizei n, GLuint *buffers))
X(glDeleteBuffers, void, (GLsizei n, const GLuint *buffers))
X(glBindBuffer, void, (GLenum target, GLuint buffer))
X(glBufferData, void, (GLenum target, GLsizeiptr size, const void *data, GLenum usage))
X(glBufferSubData, void, (GLenum target, GLintptr offset, GLsizeiptr size, const void *data))
X(glGenVertexArrays, void, (GLsizei n, GLuint *arrays))
X(glDeleteVertexArrays, void, (GLsizei n, const GLuint *arrays))
X(glBindVertexArray, void, (GLuint array))
X(glActiveTexture, void, (GLenum texture))

// textures
X(glTexImage2DMultisample, void, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations))

// shaders
X(glAttachShader, void, (GLuint program, GLuint shader))
X(glCompileShader, void, (GLuint shader))
X(glCreateProgram, GLuint, (void))
X(glCreateShader, GLuint, (GLenum type))
X(glDeleteProgram, void, (GLuint program))
X(glDeleteShader, void, (GLuint shader))
X(glGetProgramiv, void, (GLuint program, GLenum pname, GLint *params))
X(glGetProgramInfoLog, void, (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog))
X(glGetShaderiv, void, (GLuint shader, GLenum pname, GLint *params))
X(glGetShaderInfoLog, void, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog))
X(glLinkProgram, void, (GLuint program))
X(glShaderSource, void, (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length))
X(glUseProgram, void, (GLuint program))

// draw calls
X(glDrawArraysInstanced, void, (GLenum mode, GLint first, GLsizei count, GLsizei instancecount))
X(glDrawElementsInstanced, void, (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount))
X(glEnableVertexAttribArray, void, (GLuint index))
X(glDisableVertexAttribArray, void, (GLuint index))
X(glVertexAttribPointer, void, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer))
X(glVertexAttribIPointer, void, (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer))
X(glVertexAttribDivisor, void, (GLuint index, GLuint divisor))
X(glGetUniformLocation, GLint, (GLuint program, const GLchar *name))
X(glUniform1f, void, (GLint location, GLfloat v0))
X(glUniform2f, void, (GLint location, GLfloat v0, GLfloat v1))
X(glUniform3f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2))
X(glUniform4f, void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3))
X(glUniform1i, void, (GLint location, GLint v0))
X(glUniform1fv, void, (GLint location, GLsizei count, const GLfloat *value))
X(glUniform2fv, void, (GLint location, GLsizei count, const GLfloat *value))
X(glUniform3fv, void, (GLint location, GLsizei count, const GLfloat *value))
X(glUniformMatrix4fv, void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value))
X(glDrawBuffers, void, (GLsizei n, const GLenum *bufs))

// framebuffers
X(glGenFramebuffers, void, (GLsizei n, GLuint *framebuffers))
X(glDeleteFramebuffers, void, (GLsizei n, const GLuint *framebuffers))
X(glBindFramebuffer, void, (GLenum target, GLuint framebuffer))
X(glIsFramebuffer, GLboolean, (GLuint framebuffer))
X(glCheckFramebufferStatus, GLenum, (GLenum target))
X(glFramebufferTexture1D, void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))
X(glFramebufferTexture2D, void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))
X(glFramebufferTexture3D, void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset))
X(glFramebufferRenderbuffer, void, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))
X(glFramebufferTexture, void, (GLenum target, GLenum attachment, GLuint texture, GLint level))
X(glBlitFramebuffer, void, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter))
X(glGetFramebufferAttachmentParameteriv, void, (GLenum target, GLenum attachment, GLenum pname, GLint *params))

#if OS_WINDOWS
#include <gl/GL.h>
#else
// basics
X(glGetError, GLenum, (void))
X(glViewport, void, (GLint x, GLint y, GLsizei width, GLsizei height))
X(glScissor, void, (GLint x, GLint y, GLsizei width, GLsizei height))
X(glClearColor, void, (GLfloat r,GLfloat g,GLfloat b,GLfloat a))
X(glClear, void, (GLbitfield mask))
X(glBlendFunc, void, (GLenum sfactor, GLenum dfactor))
X(glDisable, void, (GLenum cap))
X(glEnable, void, (GLenum cap))
X(glPixelStorei, void, (GLenum pname, GLint param))
X(glReadPixels, void, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels))

// textures
X(glGenTextures, void, (GLsizei n, GLuint *textures))
X(glDeleteTextures, void, (GLsizei n, const GLuint *textures))
X(glBindTexture, void, (GLenum target, GLuint texture))
X(glIsTexture, GLboolean, (GLuint texture))
X(glTexParameteri, void, (GLenum target, GLenum pname, GLint param))
X(glTexImage1D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels))
X(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels))
X(glTexSubImage1D, void, (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels))
X(glTexSubImage2D, void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels))

// draw calls
X(glDrawArrays, void, (GLenum mode, GLint first, GLsizei count))
X(glDrawElements, void, (GLenum mode, GLsizei count, GLenum type, const void *indices))
#endif