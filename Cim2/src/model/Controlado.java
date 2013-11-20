package model;

public class Controlado {
	
	private int valor;
	
	//private Sensor sensor;
	
	public Controlado(Sensor sensor, int valorInicial) {
		this.valor = valorInicial;
		//this.sensor = sensor;
	}
	
	public Controlado(Sensor sensor) {
		this(sensor, 0);
	}
	
	public int getValor() {
		return this.valor;
	}
	
	public void incrementarValor(int cantidad) {
		if (cantidad < 0)
			return;
		this.valor += cantidad;
		//this.sensor.actualizar(this, this.valor);
	}
	
	public void decrementarValor(int cantidad) {
		if (cantidad < 0 || this.valor - cantidad < 0)
			return;
		this.valor -= cantidad;
		//this.sensor.actualizar(this, this.valor);
	}
	
}
