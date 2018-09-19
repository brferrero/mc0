package  
{
	import flash.display.Sprite;
	import flash.display.Loader;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.events.Event;
	import flash.xml.XMLParser;
	import flash.xml.XMLDocument;
	import flash.text.TextField;
	
	/**
	 * ...
	 * @author Bruno Ferrero, Bruno Padilha, Claudivan Ribeiro, Mariana Pacheco
	 */
	public class LeArquivo extends Sprite
	{
		private var _xml:XML;
		private var textoXML : TextField = new TextField();
		private var pontosX : Array = new Array();
		private var pontosY : Array = new Array();
		private var pontosZ : Array = new Array();
		
		//construtor
		public function LeArquivo() 
		{
			loadXMLFile();			
		}
			
		// abre o arquivo XML; o arquivo lido deve estar no mesmo diretório em que o executavel estiver sendo rodado
		private function loadXMLFile():void
		{
			var loader: URLLoader = new URLLoader();
			loader.load(new URLRequest('entrada.xml'));
			loader.addEventListener(Event.COMPLETE, processaXML);
		}
		
		// armazena dados lidos no XML em um array
		private function processaXML(e:Event):void
		{
			e.target.removeEventListener(Event.COMPLETE, processaXML);
			_xml = XML(e.target.data);
			var i: Number = 0;
		    // adiciona os pontos nos vetores
			for each (var picture:XML in _xml.ponto) {
			    pontosX[i] = picture.z
			    pontosZ[i] = picture.z
			    pontosY[i] = picture.y
			    ++i;
			}
		}
		
		//getters
		public function getPontosX (): Array
		{
			return pontosX;
		}
		
		public function getPontosY (): Array
		{
			return pontosY;
		}
		
		public function getPontosZ (): Array
		{
			return pontosZ;
		}
	}
}