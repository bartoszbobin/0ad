// Interact.h
//
// Manages main-screen interaction (screen->worldspace mapping, unit selection, ordering, etc.)
// and the hotkey message processor.
// Does this belong in GUI?

// Mark Thompson (mot20@cam.ac.uk / mark@wildfiregames.com)

#include <vector>

#include "Singleton.h"
#include "Entity.h"
#include "EntityManager.h"
#include "EntityMessage.h"
#include "Scheduler.h"
#include "Camera.h"
#include "lib/input.h"

#define MAX_BOOKMARKS 10
#define MAX_GROUPS    20

// CSelectedEntities: the singleton containing entities currently selected on the local machine.
// (including group allocations on the local machine)

struct CSelectedEntities : public Singleton<CSelectedEntities>
{
	CSelectedEntities()
	{
		clearSelection();
		m_group = -1;
		m_group_highlight = -1;
		m_contextOrder = -1;
		m_selectionChanged = true;
	}
	std::vector<HEntity> m_selected;
	std::vector<HEntity> m_groups[MAX_GROUPS];
	i8 m_group, m_group_highlight;
	bool m_selectionChanged;
	int m_contextOrder;

	void addSelection( HEntity entity );
	void removeSelection( HEntity entity );
	void setSelection( HEntity entity );
	void clearSelection();
	void removeAll( HEntity entity );
	bool isSelected( HEntity entity );
	CVector3D getSelectionPosition();

	void addToGroup( i8 groupid, HEntity entity );
	void saveGroup( i8 groupid );
	void loadGroup( i8 groupid );
	void addGroup( i8 groupid );
	void changeGroup( HEntity entity, i8 groupid );
	void highlightGroup( i8 groupid );
	void highlightNone();
	int getGroupCount( i8 groupid );
	CVector3D getGroupPosition( i8 groupid );

	void update();
	bool isContextValid( int contextOrder );
	void contextOrder( bool pushQueue = false );
	void setContext( int contextOrder );
	bool nextContext();
	bool previousContext();

	void renderSelectionOutlines();
	void renderOverlays();
};

// CMouseoverEntities: the singleton containing entities the mouse is currently hovering over or bandboxing
// ( for mouseover selection outlines )

struct SMouseoverFader
{
	HEntity entity;
	float fade;
	bool isActive;
	SMouseoverFader( HEntity _entity, float _fade = 0.0f, bool _active = true ) : entity( _entity ), fade( _fade ), isActive( _active ) {}
};

struct CMouseoverEntities : public Singleton<CMouseoverEntities>
{
	float m_fadeinrate;
	float m_fadeoutrate;
	float m_fademaximum;
	CVector2D m_worldposition;
	HEntity m_target;
	HEntity m_lastTarget;
	bool m_targetChanged;

	bool m_bandbox, m_viewall;
	u16 m_x1, m_y1, m_x2, m_y2;

	CMouseoverEntities()
	{
		m_bandbox = false;
		m_viewall = false;
		m_fadeinrate = 1.0f;
		m_fadeoutrate = 2.0f;
		m_fademaximum = 0.5f;
		m_mouseover.clear();
		m_targetChanged = true;
	}
	std::vector<SMouseoverFader> m_mouseover;
	void update( float timestep );

	void addSelection();
	void removeSelection();
	void setSelection();

	void expandAcrossScreen();
	void expandAcrossWorld();

	void renderSelectionOutlines();
	void renderOverlays();
	bool isBandbox() { return( m_bandbox ); }
	void startBandbox( u16 x, u16 y );
	void stopBandbox();
};

bool isMouseoverType( CEntity* ev, void* userdata );
bool isOnScreen( CEntity* ev, void* userdata );

int interactInputHandler( const SDL_Event* ev );

#define g_Selection CSelectedEntities::GetSingleton()
#define g_Mouseover CMouseoverEntities::GetSingleton()

