package 
{
	import com.transmote.flar.camera.FLARCamera_Away3D;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Rectangle;
	//FLAR
	import com.transmote.flar.FLARManager;
	import com.transmote.flar.camera.FLARCamera_PV3D;
	import com.transmote.flar.marker.FLARMarkerEvent;
	import com.transmote.flar.marker.FLARMarker;
	import com.transmote.flar.tracker.FLARToolkitManager;
	import com.transmote.flar.utils.geom.PVGeomUtils;
	import com.transmote.utils.time.FramerateDisplay;
	//papervision3d
	import org.papervision3d.cameras.Camera3D;
	import org.papervision3d.objects.DisplayObject3D;
	import org.papervision3d.render.LazyRenderEngine;
	import org.papervision3d.scenes.Scene3D;
	import org.papervision3d.view.Viewport3D;
	

	//propriedades do arquivo .swf gerado
	[SWF(width = '640', height = '480', backgroundColor = '#000000', frameRate = '24')]
	
	
	/**
	 * ...
	 * @author Bruno Ferrero, Bruno Padilha, Claudivan Ribeiro, Mariana Pacheco
	 * O marcador encontra-se em resources/assets/marcador.pdf.
	 **/
	
	public class Main extends Sprite 
	{
		private var fm:FLARManager;
		private var view:Viewport3D;
		private var scene:Scene3D;
		private var camera:Camera3D;
		private var lre:LazyRenderEngine;
		private var marker:FLARMarker;
		private var plot:DisplayObject3D;		
		private var g3d: Grafico3d = new Grafico3d();
		
		//textura do objeto 3D
		//[Embed(source = "../resources/assets/teste.png")] private var texture:Class;
		
		public function Main():void 
		{
			if (stage) 
				init();
			else 
				addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		//inicializa o flarmanager e prepara o palco
		private function init(e:Event = null):void 
		{
			fm = new FLARManager("../resources/flar/flarConfig.xml", new FLARToolkitManager(), stage);
			addChild(Sprite(fm.flarSource));			
			fm.addEventListener(FLARMarkerEvent.MARKER_ADDED, marker_in);
			fm.addEventListener(FLARMarkerEvent.MARKER_UPDATED, marker_stay);
			fm.addEventListener(FLARMarkerEvent.MARKER_REMOVED, marker_out);			
			fm.addEventListener(Event.INIT, start_3D);
			
		}
		
		//inicializa a engine 3D atraves da biblioteca papervision3D
		private function start_3D(e:Event):void 
		{
			scene = new Scene3D();
			camera = new FLARCamera_PV3D(fm, new Rectangle(0, 0, 640, 480));
			view = new Viewport3D(640, 480);
			lre = new LazyRenderEngine(scene, camera, view);
			addChild(view);
			addChild(new FramerateDisplay());
			object_3D();
			addEventListener(Event.ENTER_FRAME, loop);
		}
		
		//gera o objeto 3D que sera renderizado ao detectar o marcador
		private function object_3D():void
		{			
			plot = g3d.geraGrafico3D("Grafico 3D - AjuabaObi", 3);
			scene.addChild(plot);			     
		}
		
		//atualiza o objeto 3D
		private function loop(e:Event):void
		{
			if (marker)
			{				
				plot.rotationY += 1;
				plot.transform = PVGeomUtils.convertMatrixToPVMatrix(marker.transformMatrix, fm.flarSource.mirrored);			
			}
			lre.render();
		}
		//faz o objeto 3D aparecer na tela quando o marcador e detectado
		private function marker_in(e:FLARMarkerEvent):void
		{
			trace("entrou");
			plot.visible = true;
			marker = e.marker;
		}
		
		private function marker_stay(e:FLARMarkerEvent):void
		{
			plot.visible = true;
			marker = e.marker;
		}
		//o objeto desaparece quando o marcador some
		private function marker_out(e:FLARMarkerEvent):void
		{
			trace("saiu");
			plot.visible = false;
			marker = null;
		}	
	}
	
}