// Game clock (docs/rules/time_weather.md). A town step costs 1/12 of a 5-minute tick.
const SUNRISE = [8, 8, 7, 7, 7, 6, 6, 6, 7, 7, 7, 8];
const SUNSET = [18, 18, 19, 19, 19, 20, 20, 20, 19, 19, 19, 18];
const MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];

export class Clock {
  steps = 0;
  weather = 0;   // _weather: new game starts Clear (_ssnwthrs = [100, 0, …]); regional weather comes with the world map
  constructor(public minute: number, public hour: number, public date: number, public month: number) {}

  /** New game: 8:30, day 2 of month 6 (new_game.md). */
  static newGame(): Clock { return new Clock(30, 8, 2, 6); }

  daylight(): boolean { return this.hour >= SUNRISE[this.month] && this.hour < SUNSET[this.month]; }

  /** _TimCalc: hour in [appear, disappear) with wrap-around; equal bounds mean always. */
  within(appear: number, disappear: number): boolean {
    if (appear === disappear) return true;
    return appear < disappear ? this.hour >= appear && this.hour < disappear : this.hour >= appear || this.hour < disappear;
  }

  /** One town step. Returns true when the hour changed (callers re-check who is present). */
  step(): boolean {
    if (++this.steps < 12) return false;
    this.steps = 0;
    return this.tick();
  }

  /** _CalUpd1: five minutes. Returns true when the hour changed. */
  tick(): boolean {
    this.minute += 5;
    if (this.minute < 60) return false;
    this.minute = 0;
    if (++this.hour > 23) {
      this.hour = 0;
      if (++this.date > 30) { this.date = 1; this.month = (this.month + 1) % 12; }
    }
    return true;
  }

  toString(): string {
    return `${this.hour}:${String(this.minute).padStart(2, '0')} ${this.daylight() ? '☀' : '☾'}  ${MONTHS[this.month]} ${this.date}`;
  }
}
