import { expect } from 'chai';

let addon;

describe('Slicker Algorithm', () => {
  beforeEach(() => {
    addon = require('native/addon');
  });
  describe('When module is initialized', () =>{
    it('should return an object "computeSlickerArea" defined as a function', () => {
      expect(addon.computeSlickerArea).to.not.be.undefined;
      expect(typeof addon.computeSlickerArea).to.equal('function');
    });
  });
  describe('computeSlickerArea', () => {
    describe('When invoked with args (<0,0>, <1,0>, <0,1>)', () => {
      it('should return 0.5', () => {
        const area = addon.computeSlickerArea([0, 0, 1, 0, 0, 1]);
        expect(area).to.equal(0.5);
      });
    });
    describe('When invoked with incorrect length arguments', () => {
      it('should throw "RangeError: Argument length must be even"', () => {
        const invalid = addon.computeSlickerArea.bind(addon, [0, 0, 1, 0, 0]);
        expect(invalid).to.throw(RangeError);
      });
    });
    describe('When invoked with an argument other than an array', () => {
      it('should throw TypeError with message "Argument must be an array"', () => {
        const invalid = addon.computeSlickerArea.bind(addon, -1);
        expect(invalid).to.throw(TypeError);
      });
    });
  });
});

describe('Line Intersection', () => {
  beforeEach(() => {
    addon = require('native/addon');
  });
  describe('When module is initialized', () =>{
    it('should return an object with a Line template exposed', () => {
      expect(addon.Line).to.not.be.undefined;
    });
  });
  describe('When a Line is initialized without arguments', () => {
    it('should error with TypeError: Arguments must not be undefined', () => {
      const ctor = () => {
        new addon.Line();
      };
      expect(ctor).to.throw(TypeError);
    });
  });
  describe('Given two overlapping lines', () => {
    let lineA, lineB;

    beforeEach(() => {
      lineA = new addon.Line(0, 1, 1, 0);
      lineB = new addon.Line(0, 0, 1, 1);
    });
    describe('When Line::intersect is invoked on lineA with lineB', () => {
      it('should return 1', () => {
        expect(lineA.intersects(lineB)).to.equal(1);
      });
    });
  });
  describe('Given two non-intersecting lines', () => {
    let lineA, lineB;

    beforeEach(() => {
      lineA = new addon.Line(0, 0, 1, 0);
      lineB = new addon.Line(0, 1, 1, 1);
    });
    describe('When Line::intersect is invoked on lineA with lineB', () => {
      it('should return 0', () => {
        expect(lineA.intersects(lineB)).to.equal(0);
      });
    });
  });
});
