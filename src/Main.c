#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


Vec2* selected = NULL;
TransformedView tv;
Triangle triangle;

void Setup(AlxWindow* w){
	triangle = Triangle_New(
		(Vec2){ 0.1f,0.1f },
		(Vec2){ 0.1f,0.9f },
		(Vec2){ 0.9f,0.9f }
	);

	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
}

void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
	
	const float rs = 4.0f;
	const float r = TransformedView_ScreenWorldLX(&tv,rs);

	if(Stroke(ALX_MOUSE_L).PRESSED){
		selected = NULL;

		const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());

		for(int i = 0;i<3;i++){
			Vec2* p = (Vec2*)(&triangle) + i;
			const Vec2 d = Vec2_Sub(*p,m);
			
			if(Vec2_Mag2(d) < r * r){
				selected = p;
			}
		}
	}
	if(Stroke(ALX_MOUSE_L).DOWN){
		if(selected){
			const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
			*selected = m;
		}
	}

	Clear(LIGHT_BLUE);

	const Vec2 p1 = TransformedView_WorldScreenPos(&tv,triangle.p1);
	const Vec2 p2 = TransformedView_WorldScreenPos(&tv,triangle.p2);
	const Vec2 p3 = TransformedView_WorldScreenPos(&tv,triangle.p3);
	
	Triangle_RenderXWire(WINDOW_STD_ARGS,p1,p2,p3,BLACK,1.0f);
	Triangle_RenderX(WINDOW_STD_ARGS,p1,p2,p3,GREEN);

	for(int i = 0;i<3;i++){
		Vec2* p = (Vec2*)(&triangle) + i;
		const Vec2 ps = TransformedView_WorldScreenPos(&tv,*p);
		
		//Circle_RenderX(WINDOW_STD_ARGS,ps,rs,RED);
	}
}

void Delete(AlxWindow* w){
	
}

int main(){
    if(Create("3D Meshing",600,400,4,4,Setup,Update,Delete))
        Start();
    return 0;
}