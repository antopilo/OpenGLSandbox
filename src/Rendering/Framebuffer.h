#pragma once
#include "glm/vec2.hpp"
#include <GL\glew.h>
#include "Textures/Texture.h"

class FrameBuffer
{
private:

	unsigned int m_FramebufferID;
	unsigned int m_RenderBuffer;

	glm::vec2 m_Size;

	Texture* m_Texture;
	GLenum m_TextureAttachment;

public:
	FrameBuffer(bool hasRenderBuffer, glm::vec2 size, GLenum textureAttachment)
	{
		m_Size = size;
		m_TextureAttachment = textureAttachment;

		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FramebufferID);

		// Create render buffer and attach to frame buffer.
		if (hasRenderBuffer)
		{
			glGenRenderbuffers(1, &m_RenderBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);
		}
		else 
		{
			m_RenderBuffer = -1;
		}

		// Unbind
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	~FrameBuffer()
	{
		delete m_Texture;
	}

	Texture* GetTexture() const { return m_Texture; }

	void SetTexture(Texture* texture)
	{
		m_Texture = texture;

		Bind();
		m_Texture->AttachToFramebuffer(m_TextureAttachment);
		Unbind();
	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, m_Size.x, m_Size.y);
	}

	void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	glm::vec2 GetSize() const
	{
		return m_Size;
	}

	void UpdateSize(glm::vec2 size)
	{
		m_Size = size;

		// Delete frame buffer and render buffer.
		glDeleteFramebuffers(1, &m_FramebufferID);
		glDeleteRenderbuffers(1, &m_RenderBuffer);

		// Recreate resized texture.
		m_Texture->Resize(size);

		// New FBO and RBO.
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FramebufferID);

		m_Texture->AttachToFramebuffer(m_TextureAttachment);

		// Recreate render buffer
		glGenRenderbuffers(1, &m_RenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

		// Unbind.
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		//glViewport(0, 0, m_Size.x, m_Size.y);
	}

	void SetDrawBuffer(GLenum draw)
	{
		Bind();
		glReadBuffer(draw);
		Unbind();
	}

	void SetReadBuffer(GLenum read)
	{
		Bind();
		glReadBuffer(read);
		Unbind();
	}

};