package model;

public class Cisterna {
	
	private int valor;
	
	//private Controlado sumidero;
	
	public Cisterna(int valorInicial) {
		if (valorInicial < 0)
			throw new IllegalArgumentException();
		this.valor = valorInicial;
		//this.sumidero = null;
	}

	public Cisterna() {
		this(0);
	}
	
	public void setSumidero(Controlado sumidero) {
		//this.sumidero = sumidero;
	}
	
	public void incrementarValor(int cantidad) {
		if (cantidad < 0)
			return;
		this.valor += cantidad;
		//if (this.sumidero != null && this.sumidero.getValor() < 500) {
			//this.valor -= cantidad;
			//this.sumidero.incrementarValor(cantidad);
		//}
	}
	
	public void decrementarValor(int cantidad) {
		if (cantidad < 0 || this.valor - cantidad < 0)
			return;
		this.valor -= cantidad;
	}

	public int getValor() {
		return this.valor;
	}
	
}
