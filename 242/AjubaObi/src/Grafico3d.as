package  
{
	/**
	 * ...
	 * @author Bruno Ferrero, Bruno Padilha, Claudivan Ribeiro, Mariana Pacheco
	 */
	
	import com.transmote.flar.camera.FLARCamera_Away3D;
	import org.papervision3d.objects.DisplayObject3D;
	import org.papervision3d.materials.special.LineMaterial;
	import org.papervision3d.materials.ColorMaterial;
	import org.papervision3d.core.geom.Lines3D;
	import org.papervision3d.core.geom.renderables.Line3D;
	import org.papervision3d.core.geom.renderables.Vertex3D;
	import org.papervision3d.objects.primitives.Sphere;
	
	public class Grafico3d {
		
		private var pontos : Array;
		private static const MAX_SIZE : int = 500; 
        private static const AXIS_SIZE : int = 400; 
		
		private var le : LeArquivo = new LeArquivo();
		private var pontos_x : Array = le.getPontosX();
		private var pontos_y : Array = le.getPontosY();
		private var pontos_z : Array = le.getPontosZ();
		
		private static const N : int = 50;
       
		// construtor
		public function Grafico3d () {
			
		}
	   
		//metodos
		
		// Retorna um grafico 3D
		public function geraGrafico3D( nome: String, tamanho: int ): DisplayObject3D
		{
			var scenePlot: DisplayObject3D  = new DisplayObject3D(nome);
            var grafico : DisplayObject3D = new DisplayObject3D();
            
            scenePlot.rotationY=-15;
            scenePlot.rotationX=-15;
            pontos = new Array(); 
			
			// definindo as cores
			// cores : preto 0x000000
             var defaultLinha : LineMaterial = new LineMaterial(0xFF0000, .01); // cor, transparencia
			 var xAxisLinha : LineMaterial = new LineMaterial( 0x000000, .95 );             
			 var yAxisLinha : LineMaterial = new LineMaterial( 0x000000, .95 );
			 var zAxisLinha : LineMaterial = new LineMaterial( 0x000000, .95 );
             
             var dataMaterial : ColorMaterial = new ColorMaterial( 0xFF0000, .90, false );
			 
             var axes : Lines3D = new Lines3D( defaultLinha, "Axes" );
             axes.addLine( new Line3D( axes, xAxisLinha, 2, new Vertex3D( -AXIS_SIZE,0,0 ), new Vertex3D( AXIS_SIZE,0,0 ) ));
             axes.addLine( new Line3D( axes, yAxisLinha, 2, new Vertex3D( 0,-AXIS_SIZE,0 ), new Vertex3D( 0,AXIS_SIZE,0 ) ));
             axes.addLine( new Line3D( axes, zAxisLinha, 2, new Vertex3D( 0,0,-AXIS_SIZE ), new Vertex3D( 0,0,AXIS_SIZE ) ));
             
             var lines : Lines3D = new Lines3D( defaultLinha, "Lines" );
             
             grafico.addChild( axes );
             grafico.addChild( lines );
             
             var pontoAnterior : Vertex3D;
             var pontoAtual : Vertex3D = new Vertex3D();
             
            for(var i:int = 0; i < N /*50*/; i++)
            {
                pontoAnterior = pontoAtual;
                pontoAtual = new Vertex3D();
               				
				// sin() e cos() : mando os pontos na raça!!!
				//pontoAtual.x = i * tamanho * positNegat();
				//pontoAtual.y = Math.cos(i)* i * tamanho;
				//pontoAtual.z = Math.sin(i) * i * tamanho;
                pontoAtual.x = pontos_x[i] * tamanho;
				pontoAtual.y = pontos_y[i];
				pontoAtual.z = pontos_z[i];
				var ponto : Sphere = new Sphere(dataMaterial, 3);
                ponto.x = pontoAtual.x;
                ponto.y = pontoAtual.y;
                ponto.z = pontoAtual.z;
                
                grafico.addChild( ponto ); 
                
                var linha : Line3D = new Line3D(lines, defaultLinha, 3, pontoAnterior, pontoAtual);
                lines.addLine( linha );
            }
			scenePlot.addChild(grafico);
			return scenePlot;						
		}
		
		
		// retorna aleatoriamente um positivo / negativo
		private function positNegat() : int
        {
            var seed : Number = Math.random() * 100;
            if ( seed > 50 )
                return 1;
            else 
                return -1;
        }
   }   
}
	 
	