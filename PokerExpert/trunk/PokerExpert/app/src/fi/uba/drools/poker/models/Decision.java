/**
 * 
 */
package fi.uba.drools.poker.models;

/**
 * @author oscar
 *
 */
public class Decision {
	public Action action;
	public Integer betsize;
	
	
	public Decision(Action action, Integer betsize) {
		super();
		this.action = action;
		this.betsize = betsize;
	}
	public Action getAction() {
		return action;
	}
	public void setAction(Action action) {
		this.action = action;
	}
	public Integer getBetsize() {
		return betsize;
	}
	public void setBetsize(Integer betsize) {
		this.betsize = betsize;
	}
    public String getMessageAction(){
    	return this.action.getVerb();
    }
}
