package fi.uba.drools.poker.models;

public class Croupier {
	private int smallBlind;
	private int bigBlind;
	private int potSize;
	
	public int getSmallBlind() {
		return smallBlind;
	}
	public void setSmallBlind(int smallBlind) {
		this.smallBlind = smallBlind;
	}
	public int getBigBlind() {
		return bigBlind;
	}
	public void setBigBlind(int bigBlind) {
		this.bigBlind = bigBlind;
	}
	public int getPotSize() {
		return potSize;
	}
	public void setPotSize(int potSize) {
		this.potSize = potSize;
	}
	
}
