package model;

public class Sensor {
	
	public enum Limite {
		SUPERIOR, INFERIOR
	}

	//private Limite limite;
	
	private int valor;
	
	//private Cisterna cisterna;
	
	public Sensor(Limite limite, int valor, Cisterna cisterna) {
		//this.limite = limite;
		this.valor = valor;
		//this.cisterna = cisterna;
	}
	
//	public void actualizar(Controlado controlado, int nuevoValor) {
//		if (limite == Limite.SUPERIOR) {
//			if (nuevoValor > valor) {
//				int diferencia = nuevoValor - valor;
//				this.cisterna.incrementarValor(diferencia);
//				controlado.decrementarValor(diferencia);
//			}
//		} else {
//			if (nuevoValor < valor) {
//				int diferencia = valor - nuevoValor;
//				if (this.cisterna.getValor() > 0) {
//					this.cisterna.decrementarValor(diferencia);
//					controlado.incrementarValor(diferencia);
//				}
//			}
//		}
//	}

	public int getLimite() {
		return this.valor;
	}
	
	public void setLimite(int valor) {
		this.valor = valor;
	}

}
